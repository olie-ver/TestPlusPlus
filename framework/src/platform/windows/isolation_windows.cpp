#ifdef _WIN32 

#include <testpp/internal/implementation/isolation_types.hpp>
#include <windows.h>

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

namespace testpp::internal {
    namespace impl_iso {
        using Clock = std::chrono::steady_clock;

        struct Pipe {
            HANDLE read = nullptr;
            HANDLE write = nullptr;

            void closeRead() {
                if (read) {
                    CloseHandle(read);
                    read = nullptr;
                }
            }

            void closeWrite() {
                if (write) {
                    CloseHandle(write);
                    write = nullptr;
                }
            }

            ~Pipe() {
                closeRead();
                closeWrite();
            }
        };

        bool createPipe(Pipe& pipe) {
            SECURITY_ATTRIBUTES attributes{};
            attributes.nLength = sizeof(attributes);
            attributes.bInheritHandle = TRUE;

            if (!CreatePipe(
                    &pipe.read, &pipe.write, &attributes, 0)) {
                return false;
            }

            // The parent must not pass its read end to the child.
            return SetHandleInformation(
                pipe.read, HANDLE_FLAG_INHERIT, 0
            ) != 0;
        }

        void readPipe(HANDLE handle, std::string& output) {
            char buffer[4096];
            DWORD bytesRead = 0;

            while (ReadFile(
                    handle, buffer, sizeof(buffer),
                    &bytesRead, nullptr) && bytesRead > 0) {
                output.append(buffer, bytesRead);
            }
        }

        Core::CrashType classifyExitCode(DWORD code) {
            switch (code) {
                case 0xC0000005:
                    return Core::CrashType::AccessViolation;
                case 0xC0000094:
                    return Core::CrashType::DivideByZero;
                case 0xC000001D:
                    return Core::CrashType::IllegalInstruction;
                // case 0xC0000096:
                //     return Core::CrashType::PrivilegedInstruction;
                case 0xC0000409:
                    return Core::CrashType::Abort;
                default:
                    return Core::CrashType::Unknown;
            }
        }

        Core::ExecutionResult runIsolatedImpl(std::size_t testIndex, std::size_t isolationIndex, int timeLimitMs) {
            Core::ExecutionResult run{};
            const auto start = Clock::now();

            if (timeLimitMs < 0) {
                run.execution_status = Core::ExecutionStatus::InternalFrameworkError;
                run.framework_message = "Isolation timeout cannot be negative";
                return run;
            }

            Pipe stdoutPipe;
            Pipe stderrPipe;

            if (!createPipe(stdoutPipe)) {
                run.execution_status =
                    Core::ExecutionStatus::CommunicationFailure;
                run.framework_message = "Failed to create stdout pipe";
                return run;
            }

            if (!createPipe(stderrPipe)) {
                run.execution_status =
                    Core::ExecutionStatus::CommunicationFailure;
                run.framework_message = "Failed to create stderr pipe";
                return run;
            }

            char exePath[MAX_PATH]{};
            const DWORD pathLength =
                GetModuleFileNameA(nullptr, exePath, MAX_PATH);

            if (pathLength == 0 || pathLength >= MAX_PATH) {
                run.execution_status = Core::ExecutionStatus::LaunchFailed;
                run.framework_message = "Failed to locate executable";
                return run;
            }

            // The child runner parses these arguments, selects the test,
            // and dispatches the matching RUN_ISO call.
            std::string command =
                "\"" + std::string(exePath) + "\" --isolation " +
                std::to_string(testIndex) + " " +
                std::to_string(isolationIndex);

            STARTUPINFOA startup{};
            startup.cb = sizeof(startup);
            startup.dwFlags = STARTF_USESTDHANDLES;
            startup.hStdOutput = stdoutPipe.write;
            startup.hStdError = stderrPipe.write;
            startup.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

            PROCESS_INFORMATION process{};

            const BOOL launched = CreateProcessA(
                exePath,
                command.data(),
                nullptr,
                nullptr,
                TRUE,
                0,
                nullptr,
                nullptr,
                &startup,
                &process
            );

            // The parent must close its write ends so readers receive EOF.
            stdoutPipe.closeWrite();
            stderrPipe.closeWrite();

            if (!launched) {
                run.execution_status = Core::ExecutionStatus::LaunchFailed;
                run.framework_message = "CreateProcess failed (error " +
                    std::to_string(GetLastError()) + ")";
                return run;
            }

            run.process.process_id =
                static_cast<decltype(run.process.process_id)>(
                    process.dwProcessId);

            std::thread stdoutReader(
                readPipe, stdoutPipe.read,
                std::ref(run.output.stdout_text));

            std::thread stderrReader(
                readPipe, stderrPipe.read,
                std::ref(run.output.stderr_text));

            const DWORD waitResult = WaitForSingleObject(
                process.hProcess,
                static_cast<DWORD>(timeLimitMs));

            if (waitResult == WAIT_TIMEOUT) {
                run.execution_status = Core::ExecutionStatus::TimedOut;
                run.crash_type = Core::CrashType::Killed;

                if (!TerminateProcess(process.hProcess, 1)) {
                    run.framework_message =
                        "Timed out, but TerminateProcess failed (error " +
                        std::to_string(GetLastError()) + ")";
                }

                // Ensure the child has actually terminated before collecting
                // its output and releasing process resources.
                WaitForSingleObject(process.hProcess, INFINITE);
            }
            else if (waitResult == WAIT_FAILED) {
                run.execution_status =
                    Core::ExecutionStatus::InternalFrameworkError;
                run.framework_message =
                    "WaitForSingleObject failed (error " +
                    std::to_string(GetLastError()) + ")";

                // Avoid blocking forever on readers if the wait itself failed.
                TerminateProcess(process.hProcess, 1);
                WaitForSingleObject(process.hProcess, INFINITE);
            }

            DWORD exitCode = 0;
            if (!GetExitCodeProcess(process.hProcess, &exitCode)) {
                run.execution_status =
                    Core::ExecutionStatus::InternalFrameworkError;
                run.framework_message = "GetExitCodeProcess failed";
            }
            else {
                run.process.native_exit_code = static_cast<int>(exitCode);

                if (waitResult == WAIT_OBJECT_0) {
                    if (exitCode == 0) {
                        run.execution_status = Core::ExecutionStatus::Completed;
                    }
                    else {
                        run.execution_status = Core::ExecutionStatus::Crashed;
                        run.crash_type = classifyExitCode(exitCode);
                    }
                }
            }

            stdoutReader.join();
            stderrReader.join();

            stdoutPipe.closeRead();
            stderrPipe.closeRead();

            CloseHandle(process.hThread);
            CloseHandle(process.hProcess);

            run.execution_ms =
                static_cast<decltype(run.execution_ms)>(
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        Clock::now() - start).count());

            return run;
        }
    }
}

#endif
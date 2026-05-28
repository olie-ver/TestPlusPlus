#include <tester/internal/Implementation/isolation.hpp>
#include <tester/internal/Implementation/isolation_types.hpp>
#include "isolation_unix.hpp"

#include <array>
#include <fcntl.h>

namespace internal {
    namespace impl_iso {
        Core::ExecutionResult runIsolatedImpl(const std::function<void()>& func) {
            using ms = std::chrono::milliseconds;

            Core::ExecutionResult run;

            // pipe[0] = read end
            // pipe[1] = write end
            int stdoutPipe[2];
            int stderrPipe[2];

            if (pipe(stdoutPipe) == -1) {
                perror("pipe");
                run.execution_status = Core::ExecutionStatus::InternalFrameworkError;
                run.crash_type = Core::CrashType::Unknown;
                run.framework_message = "stdout pipe failed";
                return run;
            } else if (pipe(stderrPipe) == -1) {
                perror("pipe");
                run.execution_status = Core::ExecutionStatus::InternalFrameworkError;
                run.crash_type = Core::CrashType::Unknown;
                run.framework_message = "stderr pipe failed";
                return run;
            }

            pid_t child_pid = fork();

            if (child_pid == -1) {
                //fork failed
                run.execution_status = Core::ExecutionStatus::LaunchFailed;
                run.process.process_id = child_pid;
                run.process.native_exit_code = -1;
                run.crash_type = Core::CrashType::None;
            } else if (child_pid > 0) {
                //parent   

                close(stdoutPipe[1]);
                close(stderrPipe[1]);
                fcntl(stdoutPipe[0], F_SETFL, O_NONBLOCK);
                fcntl(stderrPipe[0], F_SETFL, O_NONBLOCK);

                std::array<char, 1024> stdoutBuffer{};
                std::array<char, 1024> stderrBuffer{};

                ssize_t stdoutCount;
                ssize_t stderrCount;

                auto start = std::chrono::steady_clock::now();
                int child_status = 0;
                bool timed_out = false;
                pid_t result; 
                std::chrono::steady_clock::time_point now;
                int elapsed = 0;

                while (true) {
                    //read over and over
                    while ((stdoutCount = read(stdoutPipe[0], stdoutBuffer.data(), stdoutBuffer.size())) > 0)
                    {
                        run.output.stdout_text.append(stdoutBuffer.data(), stdoutCount);
                    }

                    while ((stderrCount = read(stderrPipe[0], stderrBuffer.data(), stderrBuffer.size())) > 0)
                    {
                        run.output.stderr_text.append(stderrBuffer.data(), stderrCount);
                    }

                    result = waitpid(child_pid, &child_status, WNOHANG);
                    //check for ECHILD(result) and EINTR(result) for failures

                    if (result == child_pid) {
                        //read until no more output after child terminates
                        while ((stdoutCount = read(stdoutPipe[0], stdoutBuffer.data(), stdoutBuffer.size())) > 0)
                        {
                            run.output.stdout_text.append(stdoutBuffer.data(), stdoutCount);
                        }

                        while ((stderrCount = read(stderrPipe[0], stderrBuffer.data(), stderrBuffer.size())) > 0)
                        {
                            run.output.stderr_text.append(stderrBuffer.data(), stderrCount);
                        }

                        run.process.process_id = result;
                        break;
                    }
                    now = std::chrono::steady_clock::now();
                    elapsed = std::chrono::duration_cast<ms>(now - start).count();

                    if (elapsed > 100) { //fix the hardcode later
                        kill(child_pid, SIGKILL);

                        //read after timeout
                        while ((stdoutCount = read(stdoutPipe[0], stdoutBuffer.data(), stdoutBuffer.size())) > 0)
                        {
                            run.output.stdout_text.append(stdoutBuffer.data(), stdoutCount);
                        }

                        while ((stderrCount = read(stderrPipe[0], stderrBuffer.data(), stderrBuffer.size())) > 0)
                        {
                            run.output.stderr_text.append(stderrBuffer.data(), stderrCount);
                        }

                        result = waitpid(child_pid, &child_status, 0);

                        run.execution_status = Core::ExecutionStatus::TimedOut;
                        run.process.process_id = child_pid;
                        timed_out = true;

                        break;
                    }

                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }

                //close pipes once AFTER loop terminates instead of inside
                close(stdoutPipe[0]);
                close(stderrPipe[0]);

                if (WIFEXITED(child_status)) {
                    int exit_status = WEXITSTATUS(child_status);
                    run.execution_status = Core::ExecutionStatus::Completed;
                    run.process.native_exit_code = exit_status;

                    if (exit_status == EXIT_SUCCESS) {

                    } else {

                    }

                    //if exit_status == 0 { test passed; } else { failed; } (Conceptually)
                } else if (WIFSIGNALED(child_status)) {
                    int signal_status = WTERMSIG(child_status);
                    if (timed_out) {
                        run.execution_status = Core::ExecutionStatus::TimedOut;
                    } else {
                        run.execution_status = Core::ExecutionStatus::Crashed;
                    }

                    run.process.native_signal = signal_status;

                    // AccessViolation, //nothing on the man pages
                    // StackOverflow, //nothing on the man pages
                    // FloatingPointException, //nothing on the man pages

                    if (signal_status == SIGSEGV) {
                        run.crash_type = Core::CrashType::SegmentationFault;
                    } else if (signal_status == SIGABRT) {
                        run.crash_type = Core::CrashType::Abort;
                    } else if (signal_status == SIGFPE) {
                        run.crash_type = Core::CrashType::DivideByZero;
                    } else if (signal_status == SIGILL) {
                        run.crash_type = Core::CrashType::IllegalInstruction;
                    } else if (signal_status == SIGBUS) {
                        run.crash_type = Core::CrashType::BusError;
                    } else if (signal_status == SIGKILL) {
                        run.crash_type = Core::CrashType::Killed;
                    } else if (signal_status == SIGTRAP) {
                        run.crash_type = Core::CrashType::Trap;
                    } else {
                        run.crash_type = Core::CrashType::Unknown;
                    }

                } else if (WIFSTOPPED(child_status)) {
                    // int stop_signal = WSTOPSIG(child_status);
                }

                if (result == -1) {
                    run.execution_status = Core::ExecutionStatus::InternalFrameworkError;
                }
                run.execution_ms = elapsed;
                //not sure how to use WIFCONTINUED(child_status);

            } else {
                //child
                close(stdoutPipe[0]);
                close(stderrPipe[0]);

                dup2(stdoutPipe[1], STDOUT_FILENO);
                dup2(stderrPipe[1], STDERR_FILENO);
                close(stdoutPipe[1]);
                close(stderrPipe[1]);

                try {
                    func();
                    _exit(EXIT_SUCCESS);
                } catch (...) {
                    _exit(EXIT_FAILURE);
                }
            }

            return run;
        }
    }
}
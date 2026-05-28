#pragma once

#ifndef E_ISO_H
#define E_ISO_H

#include "../Core.hpp"
#include "../Fail.hpp"
#include "../Implementation/isolation.hpp"

//Fatal tests
#define EXPECT_DEATH(func) internal::Expects::expectDeath((func), #func, __FILE__, __LINE__)
#define EXPECT_SEGFAULT(func) internal::Expects::expectSegFault((func), #func, __FILE__, __LINE__)
#define EXPECT_ABORT(func) internal::Expects::expectAbort((func), #func, __FILE__, __LINE__)
#define EXPECT_FATAL(func) internal::Expects::expectFatal((func), #func, __FILE__, __LINE__)
#define EXPECT_NONFATAL(func) internal::Expects::expectNonFatal((func), #func, __FILE__, __LINE__)

//Exit tests
#define EXPECT_SUCCESS(func) internal::Expects::expectSuccess((func), #func, __FILE__, __LINE__)
#define EXPECT_FAILURE(func) internal::Expects::expectFailure((func), #func, __FILE__, __LINE__)
#define EXPECT_NONZERO_EXIT(func) internal::Expects::expectNonzeroExit((func), #func, __FILE__, __LINE__)
#define EXPECT_EXITCODE(func, code) internal::Expects::expectExitCode((func), #func, code, __FILE__, __LINE__)
#define EXPECT_COMPLETES(func) internal::Expects::expectCompletes((func), #func, __FILE__, __LINE__)

//Output tests
#define EXPECT_STDOUT_CONTAINS(func, content) internal::Expects::expectStdoutContains((func), (content), __FILE__, __LINE__)
#define EXPECT_STDERR_CONTAINS(func, content) internal::Expects::expectStderrContains((func), (content), __FILE__, __LINE__)
#define EXPECT_NO_STDOUT(func) internal::Expects::expectNoStdout((func), __FILE__, __LINE__)
#define EXPECT_NO_STDERR(func) internal::Expects::expectNoStderr((func), __FILE__, __LINE__)
#define EXPECT_STDOUT_MATCHES(func, content) internal::Expects::expectStdoutMatches((func), (content) __FILE__, __LINE__)
#define EXPECT_STDERR_MATCHES(func, content) internal::Expects::expectStderrMatches((func), (content) __FILE__, __LINE__)

//Sanitizer tests


//Timing/Concurrency tests


//Generic tests

namespace internal {
    namespace Expects {
        //Fatal Tests

        template<typename Func>
        inline void expectDeath(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            //need to store execution result
            Core::ExecutionResult execRes = impl_iso::death(func);
            if (execRes.execution_status != Core::ExecutionStatus::Completed) {
                Core::FailureInfo fail({
                    "Expected func to complete, but it died",
                    file,
                    line
                });
                Fail::e_fail(fail);
            }
        }

        template<typename Func>
        inline void expectSegFault(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::segfault(func);
            if (execRes.crash_type != Core::CrashType::SegmentationFault) {
                Core::FailureInfo fail({
                    "Expected func to seg fault, but it didn't",
                    file,
                    line
                });
                Fail::e_fail(fail);
            }
        }

        template<typename Func>
        inline void expectAbort(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::abort(func);
            if (execRes.crash_type != Core::CrashType::Abort) {
                Core::FailureInfo fail({
                    "Expected func to abort, but it didn't",
                    file,
                    line
                });
                Fail::e_fail(fail);
            }
        }

        template<typename Func>
        inline void expectFatal(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::fatal(func);
            if (execRes.execution_status == Core::ExecutionStatus::Completed 
                && execRes.crash_type == Core::CrashType::None)
            {
                Core::FailureInfo fail({
                    "Expected func to fail or crash, but it didn't",
                    file,
                    line
                });

                Fail::e_fail(fail);
            }
        }

        template<typename Func>
        inline void expectNonFatal(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::nonFatal(func);
            if (execRes.execution_status != Core::ExecutionStatus::Completed 
                && execRes.crash_type != Core::CrashType::None)
            {
                Core::FailureInfo fail({
                    std::string("Expected func to not have a failure, but it failed with execution status: "),
                    // + Core::ExecutionStrings[(int)execRes.execution_status] 
                    // + " and crash type: " + Core::CrashStrings[(int)execRes.crash_type],
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        //Exit Tests

        template<typename Func>
        inline void expectSuccess(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::success(func);
            if (execRes.process.native_exit_code != EXIT_SUCCESS) {
                Core::FailureInfo fail({
                    std::string("Expected func to exit with code EXIT_SUCCESS, but exited with code: "),
                    // + execRes.process.native_exit_code,
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        template<typename Func>
        inline void expectFailure(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::failure(func);
            if (execRes.process.native_exit_code != EXIT_FAILURE) {
                Core::FailureInfo fail({
                    std::string("Expected func to exit with code EXIT_FAILURE, but exited with code: "),
                    // + execRes.process.native_exit_code,
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        template<typename Func>
        inline void expectNonzeroExit(Func&& func, const char* funcName, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::nonzeroExit(func);
            if (execRes.process.native_exit_code == 0) {
                Core::FailureInfo fail({
                    std::string("Expected func to exit with a nonzero code, but exited with code: 0"),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        template<typename Func>
        inline void expectExitCode(Func&& func, const char* funcName, const int code, 
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::nonzeroExit(func);
            if (execRes.process.native_exit_code != code) {
                Core::FailureInfo fail({
                    std::string("Expected func to exit with code: code, but exited with code: "),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        template<typename Func>
        inline void expectCompletes(Func&& func, const char* funcName,
            const char* file, const uint32_t line)
        {
            Core::ExecutionResult execRes = impl_iso::completes(func);
            if (execRes.execution_status != Core::ExecutionStatus::Completed) {
                Core::FailureInfo fail({
                    std::string("Expected func to complete, but it executed with status: "),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        //Output Tests
        template <typename Func>
        inline void expectStdoutContains(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::stdoutContains(func);
            if (execRes.output.stdout_text.find(content) == std::string::npos) {
                Core::FailureInfo fail({
                    std::string("Expected stdout to contain, but it didn't. stdout: "),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        template <typename Func>
        inline void expectStderrContains(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::stderrContains(func);
            if (execRes.output.stderr_text.find(content) == std::string::npos) {
                Core::FailureInfo fail({
                    std::string("Expected stderr to contain, but it didn't. stderr: "),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        template <typename Func>
        inline void expectNoStdout(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStdout(func);
            if (!execRes.output.stdout_text.empty()) {
                Core::FailureInfo fail({
                    std::string("Expected stdout to be empty, but it wasn't. stdout: "),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        template <typename Func>
        inline void expectNoStderr(Func&& func, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStderr(func);
            if (!execRes.output.stderr_text.empty()) {
                Core::FailureInfo fail({
                    std::string("Expected stderr to be empty, but it wasn't. stderr: "),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

          template <typename Func>
        inline void expectStdoutMatches(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStdout(func);
            if (execRes.output.stdout_text != content) {
                Core::FailureInfo fail({
                    std::string("Expected stdout to be match content, but it didn't. stdout: content: "),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }

        template <typename Func>
        inline void expectStderrMatches(Func&& func, const std::string& content, const char* file, const uint32_t line) {
            Core::ExecutionResult execRes = impl_iso::noStderr(func);
            if (execRes.output.stderr_text != content) {
                Core::FailureInfo fail({
                    std::string("Expected stderr to be match content, but it didn't. stderr: content: "),
                    file,
                    line 
                });

                Fail::e_fail(fail);
            }
        }
    }
}

#endif
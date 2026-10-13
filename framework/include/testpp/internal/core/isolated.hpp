#pragma once

#ifndef TESTPP_CORE_ISOLATED_H
#define TESTPP_CORE_ISOLATED_H

#include "core.hpp"

#include <vector>
#include <cstdint>
#include <string>

namespace testpp::internal {
    namespace Core {
        /// @brief Final outcome of an isolated execution.
        enum class ExecutionStatus {
            NotRun,
            Completed,
            Crashed,
            TimedOut,
            LaunchFailed,
            CommunicationFailure,
            InternalFrameworkError,
            SanitizerFailure,
            Cancelled
        };

        inline constexpr const char* ExecutionStrings[] = {
            "Not Run",
            "Completed",
            "Crashed",
            "Timed Out",
            "Launch Failed",
            "Communication Failure",
            "Internal Error",
            "Sanitizer Failure",
            "Cancelled"
        };

        /// @brief Classification of an abnormal process termination.
        enum class CrashType {
            None,
            SegmentationFault,
            AccessViolation,
            Abort,
            DivideByZero,
            IllegalInstruction,
            BusError,
            FloatingPointException,
            Trap,
            Killed,
            Unknown
        };

        inline constexpr const char* CrashStrings[] = {
            "None",
            "Seg Fault",
            "Access Violation",
            "Abort",
            "Divide By Zero",
            "Illegal Instruction",
            "Bus Error",
            "Floating Point Exception",
            "Trap",
            "Killed",
            "Unknown"
        };

        /// @brief Native process information.
        struct ProcessInfo {
            std::int64_t process_id = -1;
            int native_exit_code = -1;
            int native_signal = -1;
        };

        /// @brief Captured standard output and standard error.
        struct OutputCapture {
            std::string stdout_text;
            std::string stderr_text;

            bool stdout_truncated = false;
            bool stderr_truncated = false;
        };

        /// @brief Sanitizer error classification.
        enum class SanitizerError {
            None,

            HeapBufferOverflow,
            StackBufferOverflow,
            UseAfterFree,
            DoubleFree,
            AllocDeallocMismatch,
            StackUseAfterReturn,

            SignedIntegerOverflow,
            InvalidShift,
            NullDereference,
            MisalignedAccess,
            DivideByZero,
            InvalidEnum,
            Unreachable,

            DataRace,
            MemoryLeak,

            Unknown
        };

        /// @brief Results reported by supported sanitizers.
        struct SanitizerInfo {
            bool asan_detected = false;
            SanitizerError asan_err = SanitizerError::None;
            std::string asan_msg;

            bool ubsan_detected = false;
            SanitizerError ubsan_err = SanitizerError::None;
            std::string ubsan_msg;

            bool tsan_detected = false;
            SanitizerError tsan_err = SanitizerError::None;
            std::string tsan_msg;

            bool lsan_detected = false;
            SanitizerError lsan_err = SanitizerError::None;
            std::string lsan_msg;
        };

        /// @brief Result of running a callable in an isolated process.
        struct ExecutionResult {
            ExecutionStatus execution_status = ExecutionStatus::NotRun;
            CrashType crash_type = CrashType::None;

            std::uint64_t execution_ms = 0;

            ProcessInfo process;
            OutputCapture output;
            SanitizerInfo sanitizers;

            std::string framework_message;
        };

        struct DeathContext {
            bool childMode;
            uint64_t targetTest;
            uint64_t targetIndex;
        };
    }
}

#endif
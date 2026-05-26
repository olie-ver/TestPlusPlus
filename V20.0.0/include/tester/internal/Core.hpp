#pragma once

#ifndef TEST_CORE_H
#define TEST_CORE_H

#include <string>
#include <functional>
#include <map>
#include <vector>

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief A core namespace containing the core data structures used by the rest of the internal namespace
    namespace Core {
        /// @brief The types of statuses a test can have after being run
        enum class TestStatus {
            Passed,
            Failed,
            Skipped,
            Unknown,
            ExpectedFailure
        };

        /// @brief A simple mapping from TestStatus => string representation
        static std::string StatusStrings[] = {"Passed", "Failed", "Skipped", "Unknown", "Expected Failure"};

        /// @brief The types of statuses a test can have after execution
        enum class ExecutionStatus
        {
            NotRun, //filtered/skipped dependencies
            Completed, //child exited normally
            Crashed, //signal/exception
            TimedOut, //watchdog kill
            LaunchFailed, //CreateProcess/fork failure
            CommunicationFailure, //pipe/socket broke
            InternalFrameworkError, //framework bug
            Cancelled //future parallel cancellation support
        };

        /// @brief A simple mapping from ExecutionStatus => string representation
        static std::string ExecutionStrings[] = 
            {
                "Not Run", "Completed", "Crashed", "Timed Out", "Launched Failed",
                "Communication Failure", "Internal Error", "Cancelled"
            };

        /// @brief Types of crashes that can happen
        enum class CrashType {
            None,
            SegmentationFault,
            AccessViolation,
            Abort,
            DivideByZero,
            IllegalInstruction,
            StackOverflow,
            BusError,
            FloatingPointException,
            Trap,
            Killed,
            Unknown
        };

        /// @brief A simple mapping from CrashType => string representation
        static std::string CrashStrings[] = 
            {
                "None", "Seg Fault", "Access Violation", "Abort", "Divide By Zero",
                "Illegal Instruction", "Stack Overflow", "Bus Error", "Floating Point Exception",
                "Trap", "Killed", "Unknown"
            };

        /// @brief An AssertionSummary struct
        /// Contains: passed/failed and warnings
        struct AssertionSummary
        {
            uint64_t passed;
            uint64_t failed;
            uint64_t warnings;
        };

        /// @brief A TimingInfo struct
        /// Contains: set up time, execution time, teardown time, total time (all ms)
        struct TimingInfo
        {
            uint64_t setup_ms;
            uint64_t execution_ms;
            uint64_t teardown_ms;
            uint64_t total_ms;
        };

        /// @brief A ProcessInfo struct
        /// Contains: process id, the native exit code, the native signal, if the core was dumped
        struct ProcessInfo
        {
            pid_t process_id;
            int native_exit_code;
            int native_signal;
            bool core_dumped;
        };

        /// @brief A struct that captures output
        /// Contains: stdout-output, stderr-output, whether or not either output was truncated
        struct OutputCapture
        {
            std::string stdout_text;
            std::string stderr_text;
            bool stdout_truncated;
            bool stderr_truncated;
        };

        /// @brief A struct containing failure information
        /// Contains: message, file, line, expression, expected, actual
        struct FailureInfo
        {
            std::string message;
            std::string file;
            uint32_t line;
            std::string expression;
            std::string expected;
            std::string actual;
        };

        /// @brief Whether or not something was run in isolation
        enum class IsolationMode
        {
            None,
            Process
        };

        /// @brief An execution strategy
        enum class ExecutionStrategy
        {
            Sequential,
            Parallel
        };

        /// @brief Struct containing retry info
        struct RetryInfo
        {
            uint32_t attempt;
            uint32_t max_attempts;
            bool flaky_pass;
        };

        /// @brief Sanitizer information
        struct SanitizerInfo
        {
            bool asan_detected;
            bool ubsan_detected;
            bool tsan_detected;
            bool lsan_detected;
        };

        /// @brief Environment information on what ran the test
        struct EnvironmentInfo
        {
            std::string hostname;
            std::string os_name;
            std::string architecture;
            uint32_t thread_id;
        };

        /// @brief The final struct for a test's execution results
        struct TestResult
        {
            std::string suiteName;
            std::string testName;

            TestStatus test_status;
            ExecutionStatus execution_status;
            CrashType crash_type;
            IsolationMode isolation_mode;
            ExecutionStrategy execution_strategy;
            AssertionSummary assertions;
            TimingInfo timing;
            ProcessInfo process;
            OutputCapture output;
            RetryInfo retry;
            SanitizerInfo sanitizers;
            EnvironmentInfo environment;
            std::vector<FailureInfo> failures;
            std::string framework_message;
        };

        /// @brief The types of time units for timeout
        enum class TimeUnit {
            Seconds,
            Milliseconds
        };

        /// @brief A Test struct that contains information about a test
        struct Test {
            std::string suite_name;
            std::string test_name;
            std::function<void()> test;

            bool operator==(const Test& other) const {
                return suite_name == other.suite_name
                    && test_name == other.test_name;
            }
        };

        /// @brief A TestRun struct that contains information about the tests being run
        struct TestRun {
            std::map<std::string, std::vector<TestResult>> results;

            int total = 0;
            double totalMs = 0.0;
        };

        /// @brief Hashes a Test struct
        struct TestHash {
            size_t operator()(const Test& p) const {
                size_t h1 = std::hash<std::string>{}(p.suite_name);
                size_t h2 = std::hash<std::string>{}(p.test_name);
                return h1 ^ (h2 << 1);
            }
        };

        //An assertion failure struct
        struct AssertionFailure : public std::exception {
            const char* what() const noexcept override {
                return "Assertion failed";
            }
        };
    }
}

#endif
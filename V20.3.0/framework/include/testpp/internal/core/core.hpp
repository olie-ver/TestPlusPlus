#pragma once

#ifndef TESTPP_CORE_H
#define TESTPP_CORE_H

#include <array>
#include <functional>
#include <string>
#include <vector>
#include <map>

namespace testpp::internal {
    namespace Core {
        enum class TestStatus {
            Passed,
            Failed,
            Skipped,
        };

        /// @brief A simple mapping from TestStatus => string representation
        constinit std::array<std::string, 3> StatusStrings{ "Passed", "Failed", "Skipped" };

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

        // struct ExecutionResult
        // {
        //     std::string framework_message = "";
        // };

        /// @brief The final struct for a test's execution results
        struct TestResult
        {
            std::string suiteName;
            std::string testName;

            TestStatus test_status;
            uint64_t execution_ms;

            std::vector<FailureInfo> failures;
        };

        /// @brief A TestRun struct that contains information about the tests being run
        struct TestRun {
            std::map<std::string, std::vector<TestResult>> results;

            int total = 0;
            long long totalMs = 0;
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
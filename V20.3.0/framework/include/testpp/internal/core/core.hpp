#pragma once

#ifndef TESTPP_CORE_H
#define TESTPP_CORE_H

#include <array>
#include <functional>
#include <string_view>
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
        constinit inline std::array<std::string_view, 3> StatusStrings{ "Passed", "Failed", "Skipped" };

        /// @brief The types of time units for timeout
        enum class TimeUnit {
            Seconds,
            Milliseconds
        };

        struct TestReference {
            std::string_view suite_name;
            std::string_view test_name;
        };

        /// @brief A Test struct that contains information about a test
        struct Test {
            std::string suite_name;
            std::string test_name;
            std::function<void()> test;
            size_t idx;

            bool operator==(const Test& other) const {
                return suite_name == other.suite_name
                    && test_name == other.test_name;
            }
        };

        struct TestGroup {
            std::vector<size_t> tests;
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
            std::string_view suiteName;
            std::string_view testName;
            size_t idx;

            TestStatus test_status;
            uint64_t execution_ms;

            std::vector<FailureInfo> failures;
        };

        /// @brief A TestRun struct that contains information about the tests being run
        struct TestRun {
            std::map<std::string_view, std::vector<TestResult>> results;

            int total = 0;
            long long totalMs = 0;
        };

        /// @brief Hashes a Test struct
        struct TestHash {
            size_t operator()(const Test& p) const {
                size_t h1 = std::hash<std::string_view>{}(p.suite_name);
                size_t h2 = std::hash<std::string_view>{}(p.test_name);
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
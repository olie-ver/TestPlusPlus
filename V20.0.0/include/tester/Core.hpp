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
        /// @brief Hashes a pair of strings
        struct PairHash {
            size_t operator()(const std::pair<std::string, std::string>& p) const {
                size_t h1 = std::hash<std::string>{}(p.first);
                size_t h2 = std::hash<std::string>{}(p.second);
                return h1 ^ (h2 << 1);
            }
        };

        /// @brief The types of statuses a test can have after being run
        enum class TestStatus {
            Passed,
            Failed,
            Skipped
        };

        /// @brief Flags for renderer verbosity
        enum class Verbosity {
            All,
            Minimum,
            Verbose,
            Default
        };

        /// @brief A Test struct that contains information about a test
        struct Test {
            std::string name;
            std::function<void()> test;
        };

        /// @brief A Failure struct that contains information about a test failure
        struct Failure {
            std::string message;
            std::string file;
            int line;
        };

        /// @brief A TestResult struct that contains information about a test's run
        struct TestResult {
            std::string suiteName;
            std::string testName;

            std::vector<Failure> failures;

            TestStatus status;
            double durationMs;
        };

        /// @brief A TestRun struct that contains information about the tests being run
        struct TestRun {
            std::map<std::string, std::vector<TestResult>> results;

            int total = 0;
            int passed = 0;
            int failed = 0;
            int skipped = 0;

            double totalMs = 0.0;
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
#pragma once

#ifndef TESTCORE_H
#define TESTCORE_H

#include <string>
#include <vector>
#include <functional>

namespace TestCore {
    /// @brief The types of statuses a test could have
    enum class TestStatus {
        Passed,
        Failed,
        Skipped
    };

    struct Test {
        std::string suite_name;
        std::string test_name;
        std::string file_name;
        std::function<void()> func;
    };

    /// @brief A struct that contains information about a test failure
    struct AssertionFailure {
        std::string message;
        std::string file;
        int line;
    };

    /// @brief A struct that contains information about a test
    struct TestResult {
        std::string suiteName;
        std::string testName;

        TestStatus status;

        std::vector<AssertionFailure> failures;

        double durationMs;

        std::string stdoutOutput;
        std::string stderrOutput;
    };

    /// @brief A struct that contains information about the tests that have been run
    struct TestRunResult {
        std::vector<TestResult> tests;

        int total = 0;
        int passed = 0;
        int failed = 0;
        int skipped = 0;

        double totalDurationMs = 0.0;
    };

}

#endif
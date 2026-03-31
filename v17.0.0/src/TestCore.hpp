#pragma once

#ifndef TESTCORE_H
#define TESTCORE_H

#include <string>
#include <vector>

namespace TestCore {
    enum class TestStatus {
        Passed,
        Failed,
        Skipped
    };

    struct AssertionFailure {
        std::string message;
        std::string file;
        int line;
    };

    struct TestResult {
        std::string suiteName;
        std::string testName;

        TestStatus status;

        std::vector<AssertionFailure> failures;

        double durationMs;

        std::string stdoutOutput;
        std::string stderrOutput;
    };

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
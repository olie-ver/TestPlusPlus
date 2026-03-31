#include "TestRunner.hpp"
#include <chrono>
#include <ctime>
#include <cmath>

namespace TestRunner {
    TestResult* CURRENT_TEST = nullptr;

    TestResult runTest(const std::string& suiteName, const std::string& testName,std::function<void()> testFunc) {
        TestResult result;
        result.suiteName = suiteName;
        result.testName = testName;
        result.status = TestStatus::Passed;

        CURRENT_TEST = &result;

        std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

        testFunc();

        std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

        result.durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

        if (!result.failures.empty()) {
            result.status = TestStatus::Failed;
        }

        CURRENT_TEST = nullptr;
        return result;
    }
}
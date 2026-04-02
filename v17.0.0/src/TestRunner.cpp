#include "TestRunner.hpp"
#include <chrono>
#include <ctime>
#include <cmath>

namespace TestRunner {
    TestResult* CURRENT_TEST = nullptr;

    std::vector<Test> TEST_REGISTRY;

    bool registerTest(
        const std::function<void()>& test, 
        const std::string& suite_name, 
        const std::string& test_name, 
        const std::string& file_name) 
    {
        TEST_REGISTRY.push_back({suite_name, test_name, file_name, test});
        return true;
    }

    void runAllRegisteredTests(TestRunResult& run) {
        for (size_t i = 0; i < TEST_REGISTRY.size(); i++) {
            TestResult result = runTest(TEST_REGISTRY[i].suite_name, TEST_REGISTRY[i].test_name, TEST_REGISTRY[i].func);
            run.tests.push_back(result);
        }
    }

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

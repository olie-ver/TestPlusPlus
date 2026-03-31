#include "Renderer.hpp"
#include <iostream>

namespace TestResultRenderer {
    void ConsoleRenderer::render(const TestRunResult& result) {
        std::cout << "Running " << result.tests.size() << " tests..." << std::endl;
        std::cout << std::endl;
        
        const std::vector<TestResult>& tests = result.tests;
        for (size_t i = 0; i < result.tests.size(); i++) {
            const TestResult& test = tests[i];
            if (test.status == TestStatus::Passed) {
                std::cout << "[PASS] " << test.suiteName << '.' << test.testName;
                std::cout << " (" << test.durationMs << " ms" << ')' << std::endl;

            } else if (test.status == TestStatus::Failed) {
                std::cout << "[FAIL] " << test.suiteName << '.' << test.testName;
                std::cout << " (" << test.durationMs << " ms" << ')' << std::endl;

                for (size_t j = 0; j < test.failures.size(); j++) {
                    const AssertionFailure& fail = test.failures[j];
                    std::cout << std::string(4, ' ') << "at: " << fail.file << ':' << fail.line << std::endl;
                    std::cout << std::string(4, ' ') << fail.message << std::endl;
                }
            } else {
                std::cout << "[SKIP] " << test.suiteName << '.' << test.testName << std::endl;
            }
            std::cout << std::endl;
        }

        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Total: " << result.tests.size();
        std::cout << " | Passed: " << result.passed;
        std::cout << " | Failed: " << result.failed;
        std::cout << " | Skipped: " << result.skipped << std::endl;
        std::cout << "Time: " << result.totalDurationMs << " ms" << std::endl;
    }
}
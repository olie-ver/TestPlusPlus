#include <tester/internal/Renderer.hpp>
#include <iostream>

namespace internal {
    namespace Renderer {
        void ConsoleRenderer::renderDefault(Core::TestRun& testRun) {
            auto& tests = testRun.results;

            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];

                    switch (result.status) {
                        case Core::TestStatus::Passed:
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.passed++;
                            break;
                    
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;

                            for (size_t j = 0; j < result.failures.size(); j++) {
                                const Core::Failure& fail = result.failures[j];
                                std::cout << "\tat: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << '\t' << fail.message << std::endl;
                                std::cout << std::endl;
                            }
                            testRun.failed++;
                            break;

                        case Core::TestStatus::Skipped:
                            std::cout << "[SKIP] " << result.suiteName << " -> " << result.testName << std::endl;
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderMinimum(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];

                    switch (result.status) {
                        case Core::TestStatus::Passed:
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.passed++;
                            break;
                    
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.failed++;
                            break;

                        case Core::TestStatus::Skipped:
                            std::cout << "[SKIP] " << result.suiteName << " -> " << result.testName << std::endl;
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderPassOnly(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.status) {
                        case Core::TestStatus::Passed: 
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.passed++;
                            break;
                        case Core::TestStatus::Failed:
                            testRun.failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderFailAll(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.status) {
                        case Core::TestStatus::Passed: 
                            testRun.passed++;
                            break;
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;

                            for (size_t j = 0; j < result.failures.size(); j++) {
                                const Core::Failure& fail = result.failures[j];
                                std::cout << "\tat: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << '\t' << fail.message << std::endl;
                                std::cout << std::endl;
                            }
                            testRun.failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }

        void ConsoleRenderer::renderFailMin(Core::TestRun& testRun) {
            auto& tests = testRun.results;
            for (auto&& it = tests.begin(); it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    const Core::TestResult& result = test[i];
                    switch (result.status) {
                        case Core::TestStatus::Passed: 
                            testRun.passed++;
                            break;
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.durationMs << " ms" << ')' << std::endl;
                            testRun.failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            testRun.skipped++;
                            break;
                    }
                }
            }
        }
    }
}
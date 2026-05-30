#include <tester/internal/PCH/pch.hpp>

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

                    switch (result.test_status) {
                        case Core::TestStatus::Passed:
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            passed++;
                            break;
                    
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;

                            for (size_t j = 0; j < result.failures.size(); j++) {
                                const Core::FailureInfo& fail = result.failures[j];
                                std::cout << "\tat: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << '\t' << fail.message << std::endl;
                                std::cout << std::endl;
                            }
                            failed++;
                            break;

                        case Core::TestStatus::Skipped:
                            std::cout << "[SKIP] " << result.suiteName << " -> " 
                                << result.testName << std::endl;
                            skipped++;
                            break;

                        case Core::TestStatus::Unknown:
                            std::cout << "[UNKNOWN] " << result.suiteName << " -> " 
                                << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            unknown++;
                            break;

                        case Core::TestStatus::ExpectedFailure:
                            std::cout << "[EXPECTED FAIL] " << result.suiteName << " -> " 
                                << result.testName << std::endl;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            expectedFailed++;
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

                    switch (result.test_status) {
                        case Core::TestStatus::Passed:
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            passed++;
                            break;
                    
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            failed++;
                            break;

                        case Core::TestStatus::Skipped:
                            std::cout << "[SKIP] " << result.suiteName << " -> " << result.testName << std::endl;
                            skipped++;
                            break;
                        
                        case Core::TestStatus::Unknown:
                            std::cout << "[UNKNOWN] " << result.suiteName << " -> " 
                                << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            unknown++;
                            break;
                        
                        case Core::TestStatus::ExpectedFailure:
                            std::cout << "[EXPECTED FAIL] " << result.suiteName << " -> " 
                                << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            expectedFailed++;
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
                    switch (result.test_status) {
                        case Core::TestStatus::Passed: 
                            std::cout << "[PASS] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            passed++;
                            break;
                        case Core::TestStatus::Failed:
                            failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            skipped++;
                            break;
                        case Core::TestStatus::Unknown:
                            unknown++;
                            break;
                        case Core::TestStatus::ExpectedFailure:
                            expectedFailed++;
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
                    switch (result.test_status) {
                        case Core::TestStatus::Passed: 
                            passed++;
                            break;
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;

                            for (size_t j = 0; j < result.failures.size(); j++) {
                                const Core::FailureInfo& fail = result.failures[j];
                                std::cout << "\tat: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << '\t' << fail.message << std::endl;
                                std::cout << std::endl;
                            }
                            failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            skipped++;
                            break;
                        case Core::TestStatus::Unknown:
                            unknown++;
                            break;
                        case Core::TestStatus::ExpectedFailure:
                            expectedFailed++;
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
                    switch (result.test_status) {
                        case Core::TestStatus::Passed: 
                            passed++;
                            break;
                        case Core::TestStatus::Failed:
                            std::cout << "[FAIL] " << result.suiteName << " -> " << result.testName;
                            std::cout << " (" << result.execution_result.execution_ms << " ms" << ')' << std::endl;
                            failed++;
                            break;
                        case Core::TestStatus::Skipped:
                            skipped++;
                            break;
                        case Core::TestStatus::Unknown:
                            unknown++;
                            break;
                        case Core::TestStatus::ExpectedFailure:
                            expectedFailed++;
                            break;
                    }
                }
            }
        }
    }
}
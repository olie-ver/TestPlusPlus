#include <tester/internal/Renderer.hpp>
#include <iostream>
#include <map>

namespace internal {
    namespace Renderer {
        void ConsoleRenderer::render(Core::TestRun& testRun) {
            std::cout << "Running " << testRun.total << " tests..." << std::endl;
 
            std::cout << std::endl;

            switch (verb) {
                case Core::Verbosity::Default:
                    renderDefault(testRun);
                    break;
                case Core::Verbosity::Minimum:
                    renderMinimum(testRun);
                    break;
                case Core::Verbosity::PassOnly:
                    renderPassOnly(testRun);
                    break;
                case Core::Verbosity::FailOnlyMin:
                    renderFailMin(testRun);
                    break;
                case Core::Verbosity::FailOnlyAll:
                    renderFailAll(testRun);
                    break;
            }

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Total: " << testRun.total;
            std::cout << " | Passed: " << testRun.passed;
            std::cout << " | Failed: " << testRun.failed;
            std::cout << " | Skipped: " << testRun.skipped << std::endl;
            std::cout << "Time: " << testRun.totalMs << " ms" << std::endl;
        }

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
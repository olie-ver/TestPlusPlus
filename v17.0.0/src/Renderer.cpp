#include <tester/Renderer.hpp>
#include <iostream>
#include <map>

namespace internal {
    namespace Renderer {
        void ConsoleRenderer::render(Core::TestRun& testRun) {
            std::cout << "Running " << testRun.results.size() << " tests..." << std::endl;
            std::cout << std::endl;
            
            std::map<std::string, std::vector<Core::TestResult>>& tests = testRun.results;

            for (std::map<std::string, std::vector<Core::TestResult>>::iterator it = tests.begin(); 
                it != tests.end(); ++it) 
            {
                const std::vector<Core::TestResult>& test = it->second;
                const std::string suite_name = it->first;
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
                                std::cout << std::string(4, ' ') << "at: " << fail.file << ":" << fail.line << std::endl;
                                std::cout << std::string(4, ' ') << fail.message << std::endl;
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

            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Total: " << testRun.total;
            std::cout << " | Passed: " << testRun.passed;
            std::cout << " | Failed: " << testRun.failed;
            std::cout << " | Skipped: " << testRun.skipped << std::endl;
            std::cout << "Time: " << testRun.totalMs << " ms" << std::endl;
        }
    }
}
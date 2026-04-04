#include "Runner.hpp"
#include <chrono>
#include <iostream>

namespace internal {
    namespace Runner {
        Core::TestResult* CURRENT_TEST;

        std::map<const std::string, std::vector<Core::Test>> REGISTRY;

        std::unordered_set<std::pair<std::string, std::string>, PairHash> ALL_TESTS;

        bool registerTest(const std::string& suite_name, const Core::Test& test) {
            const std::pair<std::string, std::string> to_register = std::make_pair(suite_name, test.name);

            auto [it, inserted] = ALL_TESTS.insert(to_register);
            if (!inserted) {
                std::cerr << "Test under suite: " << suite_name
                        << " has duplicate name: " << test.name << std::endl;
                std::abort();
            }

            ALL_TESTS.insert(to_register);
            REGISTRY[suite_name].push_back(test);
            return true;
        }

        void runAllRegisteredTests(Core::TestRun& run) {
            REGISTRY.begin();
            for (std::map<const std::string, std::vector<Core::Test>>::iterator it = REGISTRY.begin(); 
                it != REGISTRY.end(); ++it) 
            {
                const std::vector<Core::Test>&test = it->second;
                const std::string suite_name = it->first;
                size_t size = test.size();
                for (size_t i = 0; i < size; i++) {
                    run.results[suite_name].push_back(runTest(suite_name, test[i]));
                    run.total++;
                }
            }
        }

        Core::TestResult runTest(const std::string& suite_name, const Core::Test& test) {
            std::cout << "Running test: " << suite_name << " " << test.name << std::endl;
            Core::TestResult result;
            result.suiteName = suite_name;
            result.testName = test.name;
            result.status = Core::TestStatus::Passed;
            CURRENT_TEST = &result;

            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();

            test.test();

            std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

            result.durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

            if (!result.failures.empty()) {
                result.status = Core::TestStatus::Failed;
            }

            return result;
        }
    }
}
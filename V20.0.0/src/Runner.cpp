#include <tester/internal/Runner.hpp>
#include <chrono>
#include <iostream>

namespace internal {
    namespace Runner {
        Core::TestResult* CURRENT_TEST;

        Core::TestRun& makeTestRun() {
            static Core::TestRun instance;
            return instance;
        }

        std::map<std::string, std::vector<Core::Test>>& getRegistry() {
            static std::map<std::string, std::vector<Core::Test>> instance;
            return instance;
        }

        std::unordered_set<std::pair<std::string, std::string>, Core::PairHash>& getAllTests() {
            static std::unordered_set<std::pair<std::string, std::string>, Core::PairHash> instance;
            return instance;
        }

        bool registerTest(const std::string& suite_name, const Core::Test& test) {
            const std::pair<std::string, std::string> to_register = std::make_pair(suite_name, test.name);

            std::unordered_set<std::pair<std::string, std::string>, Core::PairHash>& ALL_TESTS = getAllTests();

            auto [it, inserted] = ALL_TESTS.insert(to_register);
            if (!inserted) {
                std::cerr << "Test under suite: " << suite_name
                        << " has duplicate name: " << test.name << std::endl;
                std::abort();
            }

            std::map<std::string, std::vector<Core::Test>>& REGISTRY = getRegistry();

            ALL_TESTS.insert(to_register);
            REGISTRY[suite_name].push_back(test);
            return true;
        }

        void runAllRegisteredTests(Core::TestRun& run) {
            std::map<std::string, std::vector<Core::Test>>& REGISTRY = getRegistry();

            for (auto&& it = REGISTRY.begin(); it != REGISTRY.end(); ++it) 
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
            // std::cout << "Running test: " << suite_name << " " << test.name << std::endl;
            Core::TestResult result;
            result.suiteName = suite_name;
            result.testName = test.name;
            result.status = Core::TestStatus::Passed;
            CURRENT_TEST = &result;

            std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
        
            try {
                test.test();
                std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

                result.durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

                if (!result.failures.empty()) {
                    result.status = Core::TestStatus::Failed;
                }

                return result;
            } catch (const Core::AssertionFailure&) {
                std::chrono::steady_clock::time_point end_time = std::chrono::steady_clock::now();

                result.durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();

                result.status = Core::TestStatus::Failed;

                return result;
            }
        }
    }
}
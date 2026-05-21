#include <tester/internal/Runner.hpp>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

namespace internal {
    namespace Runner {
        thread_local Core::TestResult CURRENT_TEST;

        std::atomic<size_t> next_index{0};

        Core::TestRun& makeTestRun() {
            static Core::TestRun instance;
            return instance;
        }

        // std::map<std::string, std::vector<Core::Test>>& getRegistry() {
        //     static std::map<std::string, std::vector<Core::Test>> instance;
        //     return instance;
        // }

        std::vector<Core::Test>& getRegistry() {
            static std::vector<Core::Test> instance;
            return instance;
        }


        // std::unordered_set<std::pair<std::string, std::string>, Core::PairHash>& getAllTests() {
        //     static std::unordered_set<std::pair<std::string, std::string>, Core::PairHash> instance;
        //     return instance;
        // }

        std::unordered_set<Core::Test, Core::TestHash>& getAllTests() {
            static std::unordered_set<Core::Test, Core::TestHash> instance;
            return instance;
        }

        bool registerTest(const Core::Test& test) {
        // bool registerTest(const std::string& suite_name, const Core::Test& test) {
            // const auto to_register = std::make_pair(suite_name, test.test_name);

            auto& ALL_TESTS = getAllTests();

            auto [it, inserted] = ALL_TESTS.insert(test);
            if (!inserted) {
                std::cerr << "Test under suite: " << test.suite_name
                        << " has duplicate name: " << test.test_name << std::endl;
                std::abort();
            }

            std::vector<Core::Test>& REGISTRY = getRegistry();

            REGISTRY.push_back(test);
            return true;
        }

        void runAllRegisteredTests(Core::TestRun& run, const int num_threads) {
            next_index.store(0);

            std::vector<Core::Test>& REGISTRY = getRegistry();

            //create our thread pool:
            std::vector<std::thread> threads;
            threads.reserve(num_threads - 1);

            std::vector<Core::TestResult> results;
            results.resize(REGISTRY.size());

            //threads start
            for (int i = 0; i < num_threads - 1; i++) {
                threads.emplace_back(threadWorker, std::ref(results));
            }

            //this thread does work
            threadWorker(results);

            //join them
            for (int i = 0; i < num_threads - 1; i++) {
                threads[i].join();
            }

            //aggregate results
            for (size_t i = 0; i < results.size(); i++) {
                Core::TestResult& result = results[i];
                std::string& suite_name = result.suiteName;
                run.results[suite_name].push_back(result);
                run.total++;
            }

            // for (auto&& it = REGISTRY.begin(); it != REGISTRY.end(); ++it) 
            // {
            //     const std::vector<Core::Test>&test = it->second;
            //     const std::string suite_name = it->first;
            //     size_t size = test.size();
            //     for (size_t i = 0; i < size; i++) {
            //         run.results[suite_name].push_back(runTest(suite_name, test[i]));
            //         run.total++;
            //     }
            // }
        }

        Core::TestResult runTest(const Core::Test& test) {
            // std::cout << "Running test: " << suite_name << " " << test.name << std::endl;
            // Core::TestResult result;
            // result.suiteName = test.suite_name;
            // result.testName = test.test_name;
            // result.status = Core::TestStatus::Passed;
            // CURRENT_TEST = result;

            CURRENT_TEST = {};
            CURRENT_TEST.suiteName = test.suite_name;
            CURRENT_TEST.testName = test.test_name;
            CURRENT_TEST.status = Core::TestStatus::Passed;

            using clock = std::chrono::steady_clock;
            using ms = std::chrono::milliseconds;

            clock::time_point start_time = clock::now();
        
            try {
                test.test();
                clock::time_point end_time = clock::now();

                // result.durationMs = std::chrono::duration_cast<ms>(end_time - start_time).count();

                CURRENT_TEST.durationMs =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                // if (!result.failures.empty()) {
                //     result.status = Core::TestStatus::Failed;
                // }

                if (!CURRENT_TEST.failures.empty()) {
                    CURRENT_TEST.status =  Core::TestStatus::Failed;
                }

                // return result;
                return CURRENT_TEST;
            } catch (const Core::AssertionFailure&) {
                clock::time_point end_time = clock::now();

                // result.durationMs = std::chrono::duration_cast<ms>(end_time - start_time).count();

                CURRENT_TEST.durationMs =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                // result.status = Core::TestStatus::Failed;

                CURRENT_TEST.status =  Core::TestStatus::Failed;

                // return result;
                return CURRENT_TEST;
            }
        }

        void threadWorker(std::vector<Core::TestResult>& results) {
            std::vector<Core::Test>& REGISTRY = getRegistry();

            while (true) {
                size_t index = next_index.fetch_add(1);

                if (index >= REGISTRY.size()) {
                    break;
                }

                results[index] = runTest(REGISTRY[index]);
            }
        }
    }
}
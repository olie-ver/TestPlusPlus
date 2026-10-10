#include <testpp/internal/pch/pch.hpp>


#include <testpp/internal/runner.hpp>

#include <atomic>
#include <chrono>
#include <deque>
#include <iostream>
#include <thread>

namespace testpp::internal {
    namespace Runner {
        // #ifdef _WIN32

        // DeathContext& getDeathContext()
        // {
        //     static DeathContext ctx;
        //     return ctx;
        // }

        // void runSingleTest(size_t testIndex)
        // {
        //     auto& registry = getRegistry();

        //     for (auto& test : registry)
        //     {
        //         if (test.index == testIndex)
        //         {
        //             runTest(test);
        //             return;
        //         }
        //     }

        //     std::abort();
        // }

        // #endif

        constexpr bool shouldSkip(const std::string_view& suite_name) {
            return skipSuites.contains(suite_name) || (testOnly.size() != 0 && !testOnly.contains(suite_name));
        }

        bool registerTest(Core::Test test)
        {

            // // #ifdef _WIN32
            // // test.index = REGISTRY.size();
            // // #endif

            auto [it, inserted] = allTests.insert(test);
            if (!inserted) {
                std::cerr << "Test under suite: " << test.suite_name << " has duplicate name: " << test.test_name << std::endl;
                abort();
            }

            registry.push_back(test);

            return true;
        }

        bool registerSequentialGroup(std::vector<Core::TestReference> members) {
            sequentialGroups.push_back(members);
            return true;
        }

        void runAllRegisteredTests(Core::TestRun& run, const int num_threads, 
            const int timeout, Core::TimeUnit unit)
        {   
            using clock = std::chrono::steady_clock;
            using ms = std::chrono::milliseconds;

            clock::time_point start_time = clock::now();

            std::atomic<bool> finished{false};
            std::thread watchdog;

            //create our thread pool:
            std::vector<std::thread> threads;
            threads.reserve(num_threads);

            std::vector<Core::Test> running;
            running.resize(num_threads);

            std::vector<Core::TestResult> results;
            results.resize(registry.size());

            //threads start
            for (int i = 0; i < num_threads; i++) {
                threads.emplace_back(threadWorker, std::ref(results), std::ref(running[i]));
            }

            if (timeout > 0) {
                int time = 0;
                std::string timeUnit;
                switch (unit) {
                    case Core::TimeUnit::Seconds:
                        time = timeout * 1000;
                        timeUnit = "seconds";
                        break;
                    case Core::TimeUnit::Milliseconds:
                        time = timeout;
                        timeUnit = "milliseconds";
                        break;
                }

                watchdog = createWatchdog(time, num_threads, finished, running, timeUnit, start_time);
            }

            //join them
            for (int i = 0; i < num_threads; i++) {
                threads[i].join();
            }

            finished.store(true);

            clock::time_point end_time = clock::now();

            if (watchdog.joinable()) {
                watchdog.join();
            }

            //aggregate results
            for (size_t i = 0; i < results.size(); i++) {
                Core::TestResult& result = results[i];
                std::string_view& suite_name = result.suiteName;
                run.results[suite_name].push_back(result);
                run.total++;
            }

            run.totalMs =  std::chrono::duration_cast<ms>(end_time - start_time).count();
        }

        Core::TestResult runTest(const Core::Test& test) {
            TEST_STACK.push_back({});
            Core::TestResult& CURRENT_TEST = TEST_STACK.back();
            CURRENT_TEST.suiteName = test.suite_name;
            CURRENT_TEST.testName = test.test_name;
            CURRENT_TEST.test_status = Core::TestStatus::Passed;

            // #ifdef _WIN32
            //     getDeathContext().currentDeath = 0;
            //     CURRENT_TEST.index = test.index;
            // #endif

            using clock = std::chrono::steady_clock;
            using ms = std::chrono::milliseconds;

            clock::time_point start_time = clock::now();
        
            try {
                test.test();
                clock::time_point end_time = clock::now();

                CURRENT_TEST.execution_ms =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                if (!CURRENT_TEST.failures.empty()) {
                    CURRENT_TEST.test_status =  Core::TestStatus::Failed;
                }

                Core::TestResult result = CURRENT_TEST;
                TEST_STACK.pop_back();
                return result;
            } catch (...) { //we don't care what error gets thrown, we end the test
                clock::time_point end_time = clock::now();

                CURRENT_TEST.execution_ms =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                CURRENT_TEST.test_status =  Core::TestStatus::Failed;

                Core::TestResult result = CURRENT_TEST;
                TEST_STACK.pop_back();
                return result;
            }
        }
    }
}
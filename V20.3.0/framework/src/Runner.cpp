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
            test.idx = registry.size();
            auto [it, inserted] = allTests.insert(test);

            if (!inserted) {
                std::cerr << "Test under suite: " << test.suite_name << " has duplicate name: " << test.test_name << std::endl;
                abort();
            }

            std::string name(test.suite_name);
            name.push_back('_');
            name += test.test_name;

            testToRegistry[name] = test.idx;

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
            std::unordered_set<size_t> inGroups;
            inGroups.reserve(allTests.size());

            for (size_t i  = 0; i < sequentialGroups.size(); i++) {
                Core::TestGroup group;
                for (size_t j = 0; j < sequentialGroups[i].size(); j++) {
                    std::string name(sequentialGroups[i][j].suite_name);
                    name.push_back('_');
                    name += sequentialGroups[i][j].test_name;

                    const auto& iter = testToRegistry.find(name);

                    size_t testIdx = iter->second;

                    const Core::Test& test = registry[testIdx];

                    group.tests.push_back(test.idx);
                    inGroups.insert(test.idx);
                }

                runGroups.push_back(std::move(group));
            }

            for (const auto& test : allTests) {
                if (!inGroups.contains(test.idx)) {
                    std::string name(test.suite_name);
                    name.push_back('_');
                    name += test.test_name;

                    Core::TestGroup group;
                    group.tests.push_back(test.idx);

                    runGroups.push_back(std::move(group));
                }
            }

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
            CURRENT_TEST.idx = test.idx;

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
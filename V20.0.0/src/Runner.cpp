#include <tester/internal/Runner.hpp>
#include <atomic>
#include <chrono>
#include <deque>
#include <iostream>
#include <thread>

namespace internal {
    namespace Runner {
        thread_local std::deque<Core::TestResult> TEST_STACK;

        std::atomic<size_t> next_index{0};

        Core::TestRun& getTestRun() {
            static Core::TestRun instance;
            return instance;
        }

        std::vector<Core::Test>& getRegistry() {
            static std::vector<Core::Test> instance;
            return instance;
        }

        std::unordered_set<Core::Test, Core::TestHash>& getAllTests() {
            static std::unordered_set<Core::Test, Core::TestHash> instance;
            return instance;
        }

        std::unordered_set<std::string>& getSkipSuites() {
            static std::unordered_set<std::string> instance;
            return instance;
        }

        std::unordered_set<std::string>& getTestOnly()
        {
            static std::unordered_set<std::string> instance;
            return instance;
        }

        bool registerTest(const Core::Test &test)
        {
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

        void runAllRegisteredTests(Core::TestRun& run, const int num_threads, const int timeout, Core::TimeUnit unit)
        {   
            using clock = std::chrono::steady_clock;
            using ms = std::chrono::milliseconds;

            clock::time_point start_time = clock::now();

            std::atomic<bool> finished{false};
            std::thread watchdog;
    
            next_index.store(0);

            std::vector<Core::Test>& REGISTRY = getRegistry();

            //create our thread pool:
            std::vector<std::thread> threads;
            threads.reserve(num_threads);

            std::vector<Core::Test> running;
            running.resize(num_threads);

            std::vector<Core::TestResult> results;
            results.resize(REGISTRY.size());

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

                watchdog = std::thread([&]() {
                    while (!finished.load()) {
                        clock::time_point now = clock::now();
                        int elapsed = std::chrono::duration_cast<ms>(now - start_time).count();

                        if (elapsed >= time) {
                            std::cerr << "\nGLOBAL TEST TIMEOUT EXCEEDED (" << time << ' '
                                << timeUnit << ")\n";

                            //print out what each thread is running
                            for (int i = 0; i < num_threads; i++) {
                                std::cout << "Thread " << i << " is running test: "
                                    << running[i].suite_name << " -> " << running[i].test_name << '\n';
                            }
                            std::abort();
                        }

                        std::this_thread::sleep_for(ms(100));
                    }
                });
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
                std::string& suite_name = result.suiteName;
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
            CURRENT_TEST.status = Core::TestStatus::Passed;

            using clock = std::chrono::steady_clock;
            using ms = std::chrono::milliseconds;

            clock::time_point start_time = clock::now();
        
            try {
                test.test();
                clock::time_point end_time = clock::now();

                CURRENT_TEST.durationMs =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                if (!CURRENT_TEST.failures.empty()) {
                    CURRENT_TEST.status =  Core::TestStatus::Failed;
                }

                Core::TestResult result = CURRENT_TEST;
                TEST_STACK.pop_back();
                return result;
            } catch (const Core::AssertionFailure&) {
                clock::time_point end_time = clock::now();

                CURRENT_TEST.durationMs =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                CURRENT_TEST.status =  Core::TestStatus::Failed;

                Core::TestResult result = CURRENT_TEST;
                TEST_STACK.pop_back();
                return result;
            } catch (...) {
                clock::time_point end_time = clock::now();

                CURRENT_TEST.durationMs =  std::chrono::duration_cast<ms>(end_time - start_time).count();

                CURRENT_TEST.status =  Core::TestStatus::Failed;

                Core::TestResult result = CURRENT_TEST;
                TEST_STACK.pop_back();
                return result;
            }
        }

        void threadWorker(std::vector<Core::TestResult>& results, Core::Test& running) {
            std::vector<Core::Test>& REGISTRY = getRegistry();
            auto& skip = getSkipSuites();
            auto& testOnly = getTestOnly();
    
            while (true) {
                size_t index = next_index.fetch_add(1);

                if (index >= REGISTRY.size()) {
                    break;
                }

                Core::Test& test = REGISTRY[index];

                //if the test's suite_name is marked to be skipped, skip it
                if (skip.contains(test.suite_name)) {
                    Core::TestResult skip;
                    skip.suiteName = test.suite_name;
                    skip.testName = test.test_name;
                    skip.status = Core::TestStatus::Skipped;
                    skip.durationMs = 0;

                    results[index] = skip;
                //if testOnly's size != 0 (there are suites marked to be only tested)
                //  and this test's suite_name is not one of them, skip it
                } else if (testOnly.size() != 0 && !testOnly.contains(test.suite_name)) {
                    Core::TestResult skip;
                    skip.suiteName = test.suite_name;
                    skip.testName = test.test_name;
                    skip.status = Core::TestStatus::Skipped;
                    skip.durationMs = 0;

                    results[index] = skip;
                } else {
                    running = test;

                    //only allow non-skipped tests to be run
                    results[index] = runTest(REGISTRY[index]);
                }
            }
        }
    }
}
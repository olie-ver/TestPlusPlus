#pragma once

#ifndef RUNNER_H
#define RUNNER_H

#include "core/core.hpp"

#include <deque>
#include <map>
#include <string_view>
#include <thread>
#include <unordered_set>
#include <vector>

#define STR(x) #x

#define TESTPP_UNIQUE_NAME(base, line) base##_##line
#define MAKE_UNIQUE(base, line) TESTPP_UNIQUE_NAME(base, line)

#define TEST_IMPL(suite_name, test_name, line) \
    void suite_name##_##test_name(); \
    static bool MAKE_UNIQUE(register, line) = \
        testpp::internal::Runner::registerTest( \
            {STR(suite_name), STR(test_name), suite_name##_##test_name}); \
    void suite_name##_##test_name()

#define TEST(suite_name, test_name) \
    TEST_IMPL(suite_name, test_name, __LINE__)

#define D_TEST(test_name) \
    TEST(Default, test_name)

#define SEQ(suite_name, test_name) \
    testpp::internal::Core::TestReference{STR(suite_name), STR(test_name)}

#define S_TEST_IMPL(line, ...) \
    static bool MAKE_UNIQUE(register_sequential_group, line) = \
        testpp::internal::Runner::registerSequentialGroup({__VA_ARGS__})

#define S_TEST(...) \
    S_TEST_IMPL(__LINE__, __VA_ARGS__)

/// @brief An internal namespace. Using anything from within is not advised
namespace testpp::internal {
    /// @brief An internal Runner namespace that is used for running tests
    namespace Runner {
        /// @brief The result for the current test
        inline thread_local std::deque<Core::TestResult> TEST_STACK{};

        inline Core::TestRun testRun{};

        inline std::vector<Core::Test> registry{};

        inline std::unordered_set<Core::Test, Core::TestHash> allTests{};

        inline std::vector<std::vector<Core::TestReference>> sequentialGroups{};

        inline std::unordered_set<std::string_view> skipSuites{};

        inline std::unordered_set<std::string_view> testOnly{};

        // #ifdef _WIN32

        // struct DeathContext
        // {
        //     bool childMode = false;

        //     std::size_t targetTest = std::numeric_limits<std::size_t>::max();
        //     std::size_t targetDeath = std::numeric_limits<std::size_t>::max();
        //     std::size_t currentDeath = 0;
        // };

        // DeathContext& getDeathContext();

        // void runSingleTest(size_t testIndex);

        // #endif

        /// @brief Checks if a suite should be skipped
        /// @param suite_name the suite name
        /// @return true if the suite should be skipped, false otherwise
        constexpr bool shouldSkip(const std::string_view& suite_name);

        /// @brief Adds a test to the registry under a test suite
        /// @param suite_name The name of the test suite the test is a part of 
        /// @param test The test
        bool registerTest(Core::Test test);

        /// @brief Registers a group of tests to be run sequentially
        /// @param members the tests that should be run in order
        /// @return a bool, disregard
        bool registerSequentialGroup(std::vector<Core::TestReference> members);

        /// @brief Runs all tests added to REGISTRY
        /// @param run The TestRun to put the results in
        void runAllRegisteredTests(Core::TestRun& run, const int num_threads, 
            const int timeout = 0, Core::TimeUnit unit = Core::TimeUnit::Seconds);

        /// @brief Runs the given test
        /// @param test The test to be run
        Core::TestResult runTest(const Core::Test& test);

        /// @brief A function that defines what each thread should do
        /// @param results the results that each thread is feeding into
        void threadWorker(std::vector<Core::TestResult>& results, Core::Test& running);

        /// @brief Creates a watchdog thread
        /// @return a thread
        std::thread createWatchdog(const int& time, const int& num_threads, 
            const std::atomic<bool>& finished, 
            const std::vector<Core::Test>& running, 
            const std::string& timeUnit,
            const std::chrono::steady_clock::time_point& start_time);
    }
}

#endif
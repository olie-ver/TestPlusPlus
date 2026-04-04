#pragma once

#ifndef RUNNER_H
#define RUNNER_H

#include "Core.hpp"
#include <map>
#include <vector>
#include <unordered_set>
#include <string>

#define STR(x) #x

#define UNIQUE_NAME(base, line) base##_##line
#define MAKE_UNIQUE(base, line) UNIQUE_NAME(base, line)

#define TEST_IMPL(suite_name, test_name, line) \
    void suite_name##_##test_name(); \
    static bool MAKE_UNIQUE(register, line) = \
        internal::Runner::registerTest(STR(suite_name), \
            {STR(test_name), suite_name##_##test_name}); \
    void suite_name##_##test_name()

#define TEST(suite_name, test_name) \
    TEST_IMPL(suite_name, test_name, __LINE__)

#define D_TEST(test_name) \
    TEST(Default, test_name)

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief An internal Runner namespace that is used for running tests
    namespace Runner {
        /// @brief The result for the current test
        extern Core::TestResult* CURRENT_TEST;

        /// @brief The registry containing all the tests to be run
        extern std::map<const std::string, std::vector<Core::Test>> REGISTRY;

        /// @brief Hashes a pair of strings
        struct PairHash {
            size_t operator()(const std::pair<std::string, std::string>& p) const {
                size_t h1 = std::hash<std::string>{}(p.first);
                size_t h2 = std::hash<std::string>{}(p.second);
                return h1 ^ (h2 << 1); // simple but effective
            }
        };

        /// @brief A set ensuring no duplicate tests are registered
        extern std::unordered_set<std::pair<std::string, std::string>, PairHash> ALL_TESTS;

        /// @brief Adds a test to the registry under a test suite
        /// @param suite_name The name of the test suite the test is a part of 
        /// @param test The test
        bool registerTest(const std::string& suite_name, const Core::Test& test);

        /// @brief Runs all tests added to REGISTRY
        /// @param run The TestRun to put the results in
        void runAllRegisteredTests(Core::TestRun& run);

        /// @brief Runs the given test
        /// @param test The test to be run
        Core::TestResult runTest(const std::string& suite_name, const Core::Test& test);
    }
}

#endif
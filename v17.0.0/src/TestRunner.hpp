#pragma once

#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "TestCore.hpp"
#include <functional>

using namespace TestCore;

#define STR(x) #x

#define UNIQUE_NAME(base, line) base##_##line
#define MAKE_UNIQUE(base, line) UNIQUE_NAME(base, line)

#define TEST_IMPL(suite_name, test_name, line) \
    void MAKE_UNIQUE(suite_name##_##test_name, line)(); \
    static bool MAKE_UNIQUE(register_, line) = \
        registerTest(MAKE_UNIQUE(suite_name##_##test_name, line), \
            STR(suite_name), STR(test_name), __FILE__); \
    void MAKE_UNIQUE(suite_name##_##test_name, line)()

#define TEST(suite_name, test_name) \
    TEST_IMPL(suite_name, test_name, __LINE__)

#define D_TEST(test_name) \
    TEST(Default, test_name)

namespace TestRunner {
    /// @brief The current test being run
    extern TestResult* CURRENT_TEST;

    /// @brief The registry containing every test
    extern std::vector<Test> TEST_REGISTRY;

    /// @brief Adds a test to the registry
    /// @param test the test to be registered
    bool registerTest(const std::function<void()>& test, 
        const std::string& suite_name, const std::string& test_name, const std::string& file_name);

    void runAllRegisteredTests(TestRunResult& run);

    /// @brief Runs a test
    /// @param suiteName The test suite it is a part of
    /// @param testName The name of the test
    /// @param testFunc The testing function to be run
    /// @return A TestResult containing information about what happened during the test run
    TestResult runTest(const std::string& suiteName, const std::string& testName, std::function<void()> testFunc);
}

#endif
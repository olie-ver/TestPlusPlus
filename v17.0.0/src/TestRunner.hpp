#pragma once

#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "TestCore.hpp"
#include <functional>

using namespace TestCore;

namespace TestRunner {
    extern TestResult* CURRENT_TEST;
    TestResult runTest(const std::string& suiteName, const std::string& testName,std::function<void()> testFunc);
}

#endif
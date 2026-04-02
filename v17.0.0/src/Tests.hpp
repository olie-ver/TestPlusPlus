#pragma once

#ifndef TESTS_H
#define TESTS_H

#include "TestRunner.hpp"

#define EXPECT_TRUE(cond) expectTrue((cond), __FILE__, __LINE__)

namespace Tests {
    inline void expectTrue(bool condition, const char* file, int line) {
        if (!condition) {
            TestRunner::CURRENT_TEST->failures.push_back({
                "Expected true, but got false",
                file,
                line
            });
        }
    }
}

#endif
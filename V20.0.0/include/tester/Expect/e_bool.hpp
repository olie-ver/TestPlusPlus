#pragma once

#ifndef E_BOOL_H
#define E_BOOL_H

#include "../Runner.hpp"

#define EXPECT_TRUE(cond) internal::Expect::expectTrue((cond), #cond, __FILE__, __LINE__)
#define EXPECT_FALSE(cond) internal::Expect::expectFalse((cond), #cond, __FILE__, __LINE__)

namespace internal {
    namespace Expect {
        /// @brief Test for expecting a condition to be true
        /// @param condition a condition
        /// @param expr The expression being evaluated in char* form
        /// @param file The file the condition is in
        /// @param line The line the condition is in
        inline void expectTrue(bool condition, const char* expr, const char* file, int line) 
        {
            if (!condition) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: " + std::string(expr) + " to be true",
                    file,
                    line
                });
            }
        }

        /// @brief Test for expecting a condition to be false
        /// @param condition a condition
        /// @param expr The expression being evaluated in char* form
        /// @param file The file the condition is in
        /// @param line The line the condition is in
        inline void expectFalse(bool condition, const char* expr, const char* file, int line) 
        {
            if (condition) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: " + std::string(expr) + " to be false",
                    file,
                    line
                });
            }
        }
    }
}

#endif
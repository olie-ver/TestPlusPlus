#pragma once

#ifndef E_BOOL_H
#define E_BOOL_H

#include "../Runner.hpp"

#define EXPECT_TRUE(cond) internal::Expect::expectTrue((cond), #cond, __FILE__, __LINE__)
#define EXPECT_FALSE(cond) internal::Expect::expectFalse((cond), #cond, __FILE__, __LINE__)

namespace internal {
    namespace Expect {
        /// @brief An Expects test for expecting a true value
        /// @param cond a condition
        /// @param expr the condition as an expression
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectTrue(const bool cond, const char* expr, const char* file, const int line) {
            if (!cond) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: " + std::string(expr) + " to be true",
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test for expecting a false value
        /// @param cond a condition
        /// @param expr the condition as an expression
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectFalse(const bool cond, const char* expr, const char* file, const int line) {
            if (cond) {
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
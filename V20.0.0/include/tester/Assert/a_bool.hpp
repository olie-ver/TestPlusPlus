#pragma once

#ifndef A_BOOL_H
#define A_BOOL_H

#include <exception>
#include "../Core.hpp"
#include "../Runner.hpp"

#define ASSERT_TRUE(cond) internal::Assert::assertTrue((cond), #cond, __FILE__, __LINE__)
#define ASSERT_FALSE(cond) internal::Assert::assertFalse((cond), #cond, __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief An Asserts test for asserting a true value
        /// @param cond a condition
        /// @param expr the condition as an expression
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertTrue(const bool cond, const char* expr, const char* file, const int line) {
            if (!cond) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: " + std::string(expr) + " to be true",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Asserts test for asserting a false value
        /// @param cond a condition
        /// @param expr the condition as an expression
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertFalse(const bool cond, const char* expr, const char* file, const int line) {
            if (cond) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: " + std::string(expr) + " to be false",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }
    }
}

#endif
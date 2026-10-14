#pragma once

#ifndef E_BOOL_H
#define E_BOOL_H

#include "../internal/pch/impl_pch.hpp"

#include "../internal/fail.hpp"

#define EXPECT_TRUE(cond) testpp::internal::Expects::expectTrue((cond), #cond, __FILE__, __LINE__)
#define EXPECT_FALSE(cond) testpp::internal::Expects::expectFalse((cond), #cond, __FILE__, __LINE__)

namespace testpp::internal {
    namespace Expects {
        /// @brief An Expects test for expecting a true value
        /// @param cond a condition
        /// @param expr the condition as an expression
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectTrue(const bool cond, const char* expr, const char* file, const int line) {
            auto result = impl_bool::True(cond, expr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }

        /// @brief An Expects test for expecting a false value
        /// @param cond a condition
        /// @param expr the condition as an expression
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectFalse(const bool cond, const char* expr, const char* file, const int line) {
            auto result = impl_bool::False(cond, expr, file, line);
            if (result) {
                Fail::e_fail(*result);
            }
        }
    }
}

#endif
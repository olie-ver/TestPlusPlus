#pragma once

#ifndef EXPECT_H
#define EXPECT_H

#include "Runner.hpp"

#define EXPECT_TRUE(cond) internal::Expect::expectTrue((cond), #cond, __FILE__, __LINE__)
#define EXPECT_FALSE(cond) internal::Expect::expectFalse((cond), #cond, __FILE__, __LINE__)
#define EXPECT_EQ(a, b) internal::Expect::expectEqual((a), (b), #a, #b, __FILE__, __LINE__)

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief A tests namespace containing different tests for expecting
    namespace Expect {
        //needs to be inlined because the header has a definition
        //  => header being in multiple files => multiple definitions for functions
        inline void expectTrue(bool condition, const char* expr, const char* file, int line) {
            if (!condition) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: " + std::string(expr) + " to be true",
                    file,
                    line
                });
            }
        }

        inline void expectFalse(bool condition, const char* expr, const char* file, int line) {
            if (condition) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: " + std::string(expr) + " to be false",
                    file,
                    line
                });
            }
        }

        template <typename T, typename U>
        inline void expectEqual(const T& a, const U& b, const char* a_str,
                const char* b_str, const char* file, int line) 
        {
            if (!(a == b)) {
                std::string aStr = std::string(a_str);
                std::string bStr = std::string(b_str);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a == b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }
        }
    }
}

#endif
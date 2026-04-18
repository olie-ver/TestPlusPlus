#pragma once

#ifndef E_CMP_H
#define E_CMP_H

#include "../Concepts.hpp"
#include "../Helpers.hpp"
#include "../Runner.hpp"

#define EXPECT_EQ(a, b) internal::Expects::expectEquals((a), (b), __FILE__, __LINE__)
#define EXPECT_NE(a, b) internal::Expects::expectNotEquals((a), (b), __FILE__, __LINE__)

namespace internal {
    namespace Compare {
        /// @brief An Expects test for expecting two values to be equal
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires Concepts::HasEQ<A, B>
        inline void expectEquals(A& a, B& b, const char* file, const int line) {
            if (!(a == b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a == b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test for expecting two values to be not equal
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires (Concepts::HasNE<A, B> || Concepts::HasEQ<A, B>)
        inline void expectNotEquals(A& a, B& b, const char* file, const int line) {
            if constexpr(Concepts::HasNE<A, B>) {
                if (!(a != b)) {
                    std::string aStr = Helpers::toString(a);
                    std::string bStr = Helpers::toString(b);
                    Runner::CURRENT_TEST->failures.push_back({
                        "Expected: a != b \n      a = " + aStr + "\n      b = " + bStr,
                        file,
                        line
                    });
                }
            } else {
                if (a == b) {
                    std::string aStr = Helpers::toString(a);
                    std::string bStr = Helpers::toString(b);
                    Runner::CURRENT_TEST->failures.push_back({
                        "Expected: a != b \n      a = " + aStr + "\n      b = " + bStr,
                        file,
                        line
                    });
                }
            }
        }
    }
}

#endif
#pragma once

#ifndef A_CMP_H
#define A_CMP_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include "../Helpers.hpp"
#include "../Runner.hpp"

#define ASSERT_EQ(a, b) internal::Assert::assertEquals((a), (b), __FILE__, __LINE__)
#define ASSERT_NE(a, b) internal::Assert::assertNotEquals((a), (b), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief An Asserts test for asserting two values to be equal
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires Concepts::HasEQ<A, B>
        inline void assertEquals(A& a, B& b, const char* file, const int line) {
            if (!(a == b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a == b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }

            throw Core::AssertionFailure;
        }

        /// @brief An Asserts test for asserting two values to be not equal
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires (Concepts::HasNE<A, B> || Concepts::HasEQ<A, B>)
        inline void assertNotEquals(A& a, B& b, const char* file, const int line) {
            if constexpr(Concepts::HasNE<A, B>) {
                if (!(a != b)) {
                    std::string aStr = Helpers::toString(a);
                    std::string bStr = Helpers::toString(b);
                    Runner::CURRENT_TEST->failures.push_back({
                        "Expected: a != b \n      a = " + aStr + "\n      b = " + bStr,
                        file,
                        line
                    });

                    throw Core::AssertionFailure;
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

                    throw Core::AssertionFailure;
                }
            }
        }

        /// @brief An Assert test for asserting that the first argument to be strictly less than the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasLT<A, B>)
        inline void assertLessThan(A a, B b, const char* file, const int line) {
            if (!(a < b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a < b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
                
                throw Core::AssertionFailure;
            }
        }

        /// @brief An Assert test for asserting that the first argument to be less than or equal to the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasLE<A, B>)
        inline void assertLessThanEqual(A a, B b, const char* file, const int line) {
            if (!(a <= b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a <= b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });

                throw Core::AssertionFailure;
            }
        }

        /// @brief An Assert test for asserting that the first argument to be strictly greater than the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasGT<A, B>)
        inline void assertGreaterThan(A a, B b, const char* file, const int line) {
            if (!(a > b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a <= b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }
        }

        /// @brief An Assert test for asserting that the first argument to
        ///         be strictly greater than or equal to the second
        /// @tparam A a generic type
        /// @tparam B a generic type
        /// @param a the first argument
        /// @param b the second argument
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B>
        requires(Concepts::HasGE<A, B>)
        inline void assertGreaterThanEqual(A a, B b, const char* file, const int line) {
            if (!(a >= b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a <= b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }
        }
    }
}

#endif
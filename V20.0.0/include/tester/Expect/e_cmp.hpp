#pragma once

#ifndef E_CMP_H
#define E_CMP_H

#include "../Runner.hpp"
#include "../Helpers.hpp"

#define EXPECT_EQ(a, b) internal::Expect::expectEqual((a), (b), __FILE__, __LINE__)
#define EXPECT_NE(a, b) internal::Expect::expectNotEqual((a), (b), __FILE__, __LINE__)
#define EXPECT_LT(a, b) internal::Expect::expectLessThan((a), (b), __FILE__, __LINE__)
#define EXPECT_LE(a, b) internal::Expect::expectLessThanEqual((a), (b), __FILE__, __LINE__)
#define EXPECT_GT(a, b) internal::Expect::expectGreaterThan((a), (b), __FILE__, __LINE__)
#define EXPECT_GE(a, b) internal::Expect::expectGreaterThanEqual((a), (b), __FILE__, __LINE__)

namespace internal {
    namespace Expect {
        /// @brief Test for expecting a two values to be equal
        /// @tparam T A generic type
        /// @tparam U A generic type 
        /// @param a a T
        /// @param b a U
        /// @param file The file the test is in
        /// @param line The line the test is on
        template <typename T, typename U>
        inline void expectEqual(const T& a, const U& b, const char* file, int line) 
        {
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

        /// @brief Test for expecting a two values to be not equal
        /// @tparam T A generic type
        /// @tparam U A generic type 
        /// @param a a T
        /// @param b a U
        /// @param file The file the test is in
        /// @param line The line the test is on
        template <typename T, typename U>
        inline void expectNotEqual(const T& a, const U& b, const char* file, int line) 
        {
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

        /// @brief Test for expecting one value to be strictly less than the other
        /// @tparam T A generic type
        /// @tparam U A generic type 
        /// @param a a T
        /// @param b a U
        /// @param file The file the test is in
        /// @param line The line the test is on
        template <typename T, typename U>
        inline void expectLessThan(const T& a, const U&b, const char* file, int line) 
        {
            if (!(a < b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a < b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }
        }

        /// @brief Test for expecting one value to be less than or equal to the other
        /// @tparam T A generic type
        /// @tparam U A generic type 
        /// @param a a T
        /// @param b a U
        /// @param file The file the test is in
        /// @param line The line the test is on
        template <typename T, typename U>
        inline void expectLessThanEqual(const T& a, const U&b, const char* file, int line) 
        {
            if (!(a <= b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a <= b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }
        }

        /// @brief Test for expecting one value to be strictly greater than the other
        /// @tparam T A generic type
        /// @tparam U A generic type 
        /// @param a a T
        /// @param b a U
        /// @param file The file the test is in
        /// @param line The line the test is on
        template <typename T, typename U>
        inline void expectGreaterThan(const T& a, const U&b, const char* file, int line) 
        {
            if (!(a > b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a > b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }
        }

        /// @brief Test for expecting one value to be greater than or equal to the other
        /// @tparam T A generic type
        /// @tparam U A generic type 
        /// @param a a T
        /// @param b a U
        /// @param file The file the test is in
        /// @param line The line the test is on
        template <typename T, typename U>
        inline void expectGreaterThanEqual(const T& a, const U&b, const char* file, int line) 
        {
            if (!(a >= b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected: a >= b \n      a = " + aStr + "\n      b = " + bStr,
                    file,
                    line
                });
            }
        }
    }
}

#endif
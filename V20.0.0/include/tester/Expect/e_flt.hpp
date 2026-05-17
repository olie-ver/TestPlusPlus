#pragma once

#ifndef E_FLT_H
#define E_FLT_H

#include "../Concepts.hpp"
#include "../Runner.hpp"

#define EXPECT_NEAR_3_ARGS(first, second, abs_tol) \
    internal::Expects::absolutelyEqual((first), (second), (abs_tol), __FILE__, __LINE__)

#define EXPECT_NEAR_4_ARGS(first, second, abs_tol, rel_tol) \
    internal::Expects::nearlyEqual((first), (second), (abs_tol), (rel_tol), __FILE__, __LINE__)

#define GET_5TH_ARG(arg1, arg2, arg3, arg4, arg5, ...) arg5

#define EXPECT_NEAR_MACRO_CHOOSER(...) \
    GET_5TH_ARG(__VA_ARGS__, EXPECT_NEAR_4_ARGS, EXPECT_NEAR_3_ARGS)

//The actual tests
#define EXPECT_NEAR(...) EXPECT_NEAR_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define EXPECT_REL_NEAR(first, second, rel_tol) \
    internal::Expects::relativelyEqual((first), (second), (rel_tol), __FILE__, __LINE__)

#define EXPECT_ABS_NEAR(first, second, abs_tol) \
    internal::Expects::absolutelyEqual((first), (second), (abs_tol), __FILE__, __LINE__)

#define EXPECT_NAN(number) internal::Expects::isNaN((number), __FILE__, __LINE__)
#define EXPECT_NOT_NAN(number) internal::Expects::isNotNan((number), __FILE__, __LINE__)

#define EXPECT_INF(number) internal::Expects::isInf((number), __FILE__, __LINE__)
#define EXPECT_POS_INF(number) internal::Expects::isPosInf((number), __FILE__, __LINE__)
#define EXPECT_NEG_INF(number) internal::Expects::isNegInf((number), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        /// @brief Checks if two floating point values are "close enough" to each other
        /// @tparam A a generic floating point type
        /// @tparam B a generic floating point type
        /// @tparam T1 a generic floating point type
        /// @tparam T2 a generic floating point type
        /// @param a the first value
        /// @param b the second value
        /// @param abs_tol the absolute tolerance
        /// @param rel_tol the relative tolerance
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B, typename T1, typename T2>
        requires Concepts::CommonFloat<A, B, T1, T2>
        inline void nearlyEqual(A a, B b, T1 abs_tol, T2 rel_tol, const char* file, int line) {
            using T = std::common_type_t<A, B, T1, T2>;

            T aa = static_cast<T>(a);
            T bb = static_cast<T>(b);
            T absTol = static_cast<T>(abs_tol);
            T relTol = static_cast<T>(rel_tol);

            if (std::abs(aa - bb) > std::max(std::abs(absTol), std::abs(relTol) * std::max(std::abs(aa), std::abs(bb)))) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected |a - b| <= max(abs_tol, rel_tol * max(|a|, |b|))") 
                        + "\n      a = " + Helpers::toString(aa) 
                        + "\n      b = " + Helpers::toString(bb) 
                        + "\n      abs_tol = " + Helpers::toString(absTol)
                        + "\n      rel_tol = " + Helpers::toString(relTol),
                    file,
                    line
                });
            }
        }

        /// @brief Checks if two floating point values are absolutely near to each other
        /// @tparam A a generic floating point type
        /// @tparam B a generic floating point type
        /// @tparam T1 a generic floating point type
        /// @param a the first value
        /// @param b the second value
        /// @param abs_tol the absolute tolerance
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1> //add in an extra T1 to satisfy the concept
        inline void absolutelyEqual(A a, B b, T1 abs_tol, const char* file, int line) {
            using T = std::common_type_t<A, B, T1>;
            
            T aa = static_cast<T>(a);
            T bb = static_cast<T>(b);
            T absTol = static_cast<T>(abs_tol);

            if (std::abs(aa - bb) > std::abs(absTol)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected |a - b| <= |abs_tol|") 
                        + "\n      a = " + Helpers::toString(aa) 
                        + "\n      b = " + Helpers::toString(bb) 
                        + "\n      abs_tol = " + Helpers::toString(absTol),
                    file,
                    line
                });
            }
        }

        /// @brief Checks if two floating point values are relatively near to each other
        /// @tparam A a generic floating point type
        /// @tparam B a generic floating point type
        /// @tparam T1 a generic floating point type
        /// @param a the first value
        /// @param b the second value
        /// @param rel_tol the relative tolerance
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1>
        inline void relativelyEqual(A a, B b, T1 rel_tol, const char* file, int line) {
            using T = std::common_type_t<A, B, T1>;

            T aa = static_cast<T>(a);
            T bb = static_cast<T>(b);
            T relTol = static_cast<T>(rel_tol);

            if (std::abs(aa - bb) > std::abs(relTol) * std::max(std::abs(aa), std::abs(bb))) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected |a - b| <= rel_tol * max(|a|, |b|)") 
                        + "\n      a = " + Helpers::toString(aa) 
                        + "\n      b = " + Helpers::toString(bb) 
                        + "\n      rel_tol = " + Helpers::toString(relTol),
                    file,
                    line
                });
            }
        }

        /// @brief Checks if something is NaN
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function is called from
        /// @param line the line the function is called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isNaN(T val, const char* file, int line) {
            if (val != NAN) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected val to be NaN") + "\n      val = " + val,
                    file,
                    line
                });
            }
        }

        /// @brief Checks if something is not NaN
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function is called from
        /// @param line the line the function is called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isNotNaN(T val, const char* file, int line) {
            if (val != NAN) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected val to not be NaN \n      val = NaN",
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test for checking if a floating point value is infinity/negative infinity
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isInf(T val, const char* file, const int line) {
            if (!std::isinf(val)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected val to be inf \n      val = " + val),
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test for checking if a floating point value is positive infinity
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isPosInf(T val, const char* file, const int line) {
            if (!std::isinf(val)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected val to be positive infinity but it wasn't \n      val = " + val),
                    file,
                    line
                });
            } else if (std::isinf(val) && val < 0.0) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected val to be positive infinity, but it wasn't \n      val = " + val),
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test for checking if a floating point value is negative infinity
        /// @tparam T a floating point type
        /// @param val the value
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline void isNegInf(T val, const char* file, const int line) {
            if (!std::isinf(val)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected val to be negative infinity but it wasn't \n      val = " + val),
                    file,
                    line
                });
            } else if (std::isinf(val) && val > 0.0) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected val to be negative infinity, but it wasn't \n      val = " + val),
                    file,
                    line
                });
            }
        }
    }
}

#endif
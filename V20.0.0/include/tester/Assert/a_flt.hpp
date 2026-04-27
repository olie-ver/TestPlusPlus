#pragma once

#ifndef A_FLT_H
#define A_FLT_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include "../Runner.hpp"

#define ASSERT_NEAR_3_ARGS(first, second, abs_tol) \
    internal::Assert::absolutelyEqual((first), (second), (abs_tol), __FILE__, __LINE__)

#define ASSERT_NEAR_4_ARGS(first, second, abs_tol, rel_tol) \
    internal::Assert::nearlyEqual((first), (second), (abs_tol), (rel_tol), __FILE__, __LINE__)

#define GET_5TH_ARG(arg1, arg2, arg3, arg4, arg5, ...) arg5

#define ASSERT_NEAR_MACRO_CHOOSER(...) \
    GET_5TH_ARG(__VA_ARGS__, ASSERT_NEAR_4_ARGS, ASSERT_NEAR_3_ARGS)

//The actual tests
#define ASSERT_NEAR(...) ASSERT_NEAR_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

#define ASSERT_REL_NEAR(first, second, rel_tol) \
    internal::Assert::relativelyEqual((first), (second), (rel_tol), __FILE__, __LINE__)

#define ASSERT_ABS_NEAR(first, second, abs_tol) \
    internal::Assert::absolutelyEqual((first), (second), (abs_tol), __FILE__, __LINE__)

#define ASSERT_NAN(number) internal::Assert::isNaN((number), __FILE__, __LINE__)
#define ASSERT_NOT_NAN(number) internal::Assert::isNotNan((number), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
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

                throw Core::AssertionFailure();
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

                throw Core::AssertionFailure();
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

                throw Core::AssertionFailure();
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

                throw Core::AssertionFailure();
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
            static_assert(std::is_floating_point<T>::value);

            if (val != NAN) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected val to not be NaN + \n      val = NaN",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }
    }
}

#endif
#pragma once

#ifndef E_FLT_H
#define E_FLT_H

#include "../Runner.hpp"
#include "../Helpers.hpp"
#include <type_traits>
#include <algorithm>
#include <string>

#define EXPECT_NEAR(first, second, abs_tol, rel_tol) \
    internal::Expect::nearlyEqual((first), (second), (abs_tol), (rel_tol), __FILE__, __LINE__)

namespace internal {
    namespace Expect {
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
        void nearlyEqual(A a, B b, T1 abs_tol, T2 rel_tol, const char* file, int line) {
            using T = std::common_type_t<A, B, T1, T2>;
            static_assert(std::is_floating_point<T>::value);

            T aa = static_cast<T>(a);
            T bb = static_cast<T>(b);
            T absTol = static_cast<T>(abs_tol);
            T relTol = static_cast<T>(rel_tol);

            if (std::abs(aa - bb) > std::max(absTol, relTol * std::max(std::abs(aa), std::abs(bb)))) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected |a - b| <= max(abs_tol, rel_tol * max(|a|, |b|)") 
                        + "\n      a = " + Helpers::toString(aa) 
                        + "\n      b = " + Helpers::toString(bb) 
                        + "\n      abs_tol = " + Helpers::toString(absTol)
                        + "\n      rel_tol = " + Helpers::toString(relTol),
                    file,
                    line
                });
            }
        }
    }
}

#endif
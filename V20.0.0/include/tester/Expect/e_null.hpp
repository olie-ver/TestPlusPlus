#pragma once

#ifndef E_NULL_H
#define E_NULL_H

#include "../Runner.hpp"
#include "../Helpers.hpp"
#include <type_traits>

#define EXPECT_NULL(val) internal::Expect::isNull((val), __FILE__, __LINE__)
#define EXPECT_NOT_NULL(val) internal::Expect::isNotNull((val), __FILE__, __LINE__)

namespace internal {
    namespace Expect {
        /// @brief Checks if something is null
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        inline void isNull(const T& val, const char* file, int line) {
            static_assert(
                std::is_convertible<decltype(val == nullptr), bool>::value,
                "isNull requires a type comparable to nullptr"
            );

            if (val != nullptr) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected val to be nullptr.\n val = " + Helpers::toString(val),
                    file,
                    line
                });
            }
        }

        /// @brief Checks if something is not null
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        inline void isNotNull(const T& val, const char* file, int line) {
            static_assert(
                std::is_convertible<decltype(val == nullptr), bool>::value,
                "isNotNull requires a type comparable to nullptr"
            );

            if (val == nullptr) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected val to not be a nullptr.\n val = nullptr ",
                    file,
                    line
                });
            }
        }
    }
}

#endif
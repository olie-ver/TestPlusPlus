#pragma once

#ifndef E_NULL_H
#define E_NULL_H

#include "../Concepts.hpp"
#include "../Runner.hpp"

#define EXPECT_NULL(val) internal::Expects::expectNull((val), __FILE__, __LINE__)
#define EXPECT_NOT_NULL(val) internal::Expects::expectNotNull((val), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        /// @brief An Expects test to check if something is the nullptr
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Nullable<T>
        inline void expectNull(const T& val, const char* file, const int line) {
            if (val != nullptr) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected val to be nullptr.\n val = " + Helpers::toString(val),
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test to check if something is not the nullptr
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Nullable<T>
        inline void expectNotNull(const T& val, const char* file, const int line) {
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
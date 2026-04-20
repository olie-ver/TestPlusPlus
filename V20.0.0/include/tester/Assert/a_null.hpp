#pragma once

#ifndef A_NULL_H
#define A_NULL_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include "../Runner.hpp"

#define ASSERT_NULL(val) internal::Assert::assertNull((val), __FILE__, __LINE__)
#define ASSERT_NOT_NULL(val) internal::Assert::assertnotNull((val), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief An Assert test to assert if something is the nullptr
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Nullable<T>
        inline void assertNull(const T& val, const char* file, const int line) {
            if (val != nullptr) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected val to be nullptr.\n val = " + Helpers::toString(val),
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test to assert if something is not the nullptr
        /// @tparam T a type that can be compared to nullptr
        /// @param val the value
        /// @param file the file the function was called in
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Nullable<T>
        inline void assertNotNull(const T& val, const char* file, const int line) {
            if (val == nullptr) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected val to not be a nullptr.\n val = nullptr ",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }
    }
}

#endif
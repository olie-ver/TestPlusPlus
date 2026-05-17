#pragma once

#ifndef A_PRED_H
#define A_PRED_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include "../Helpers.hpp"
#include "../Runner.hpp"
#include <algorithm>
#include <ranges>

#define ASSERT_ALL(container, condition) \
    internal::Assert::assertAllOf((container), (condition), __FILE__, __LINE__)

#define ASSERT_SOME(container, condition) \
    internal::Assert::assertAnyOf((container), (condition), __FILE__, __LINE__)

#define ASSERT_NONE(container, condition) \
    internal::Assert::assertNoneOf((container), (condition), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertAllOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::all_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Not every element satisfied the passed in condition",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertAllOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::all_of(t, t + N, func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Not every element satisfied the passed in condition",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertAnyOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::any_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "No element satisfied the passed in condition",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertAnyOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::any_of(t, t + N, func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "No element satisfied the passed in condition",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertNoneOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::none_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "At least one element satisfied the passed in condition",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertNoneOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::none_of(t, t + N, func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "At least one element satisfied the passed in condition",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }
    }
}

#endif
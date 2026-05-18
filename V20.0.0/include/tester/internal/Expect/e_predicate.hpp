#pragma once

#ifndef E_PRED_H
#define E_PRED_H

#include "../Concepts.hpp"
#include "../Helpers.hpp"
#include "../Runner.hpp"
#include <algorithm>
#include <ranges>

#define EXPECT_ALL(container, condition) \
    internal::Expects::expectAllOf((container), (condition), __FILE__, __LINE__)

#define EXPECT_SOME(container, condition) \
    internal::Expects::expectAnyOf((container), (condition), __FILE__, __LINE__)

#define EXPECT_NONE(container, condition) \
    internal::Expects::expectNoneOf((container), (condition), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void expectAllOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::all_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Not every element satisfied the passed in condition",
                    file,
                    line
                });
            }
        }

        template <typename T, size_t N, typename Func>
        inline void expectAllOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::all_of(t, t + N, func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Not every element satisfied the passed in condition",
                    file,
                    line
                });
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void expectAnyOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::any_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "No element satisfied the passed in condition",
                    file,
                    line
                });
            }
        }

        template <typename T, size_t N, typename Func>
        inline void expectAnyOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::any_of(t, t + N, func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "No element satisfied the passed in condition",
                    file,
                    line
                });
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void expectNoneOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::none_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "At least one element satisfied the passed in condition",
                    file,
                    line
                });
            }
        }

        template <typename T, size_t N, typename Func>
        inline void expectNoneOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::none_of(t, t + N, func)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "At least one element satisfied the passed in condition",
                    file,
                    line
                });
            }
        }
    }
}

#endif
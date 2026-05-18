#pragma once

#ifndef PRED_H
#define PRED_H

#include "../Core.hpp"
#include <optional>
#include <ranges>

namespace internal {
    namespace impl_pred {
        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline std::optional<Core::Failure>
        allOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::all_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                return Core::Failure({
                    "Not every element satisfied the passed in condition",
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, size_t N, typename Func>
        inline std::optional<Core::Failure>
        allOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::all_of(t, t + N, func)) {
                return Core::Failure({
                    "Not every element satisfied the passed in condition",
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline std::optional<Core::Failure>
       anyOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::any_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                return Core::Failure({
                    "No element satisfied the passed in condition",
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, size_t N, typename Func>
        inline std::optional<Core::Failure>
        anyOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::any_of(t, t + N, func)) {
                return Core::Failure({
                    "No element satisfied the passed in condition",
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline std::optional<Core::Failure>
        noneOf(const T& t, const Func&&, const char* file, const int line) {
            if (!std::none_of(std::ranges::cbegin(t), std::ranges::cend(t), func)) {
                return Core::Failure({
                    "At least one element satisfied the passed in condition",
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, size_t N, typename Func>
        inline std::optional<Core::Failure>
        noneOf(const T(& t)[N], const Func&&, const char* file, const int line) {
            if (!std::none_of(t, t + N, func)) {
                return Core::Failure({
                    "At least one element satisfied the passed in condition",
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif
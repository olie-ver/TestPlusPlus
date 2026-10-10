#pragma once

#ifndef A_PRED_H
#define A_PRED_H

#include "internal/pch/impl_pch.hpp"

#include "internal/fail.hpp"

#define ASSERT_ALL(container, condition) \
    testpp::internal::Assert::assertAllOf((container), (condition), __FILE__, __LINE__)

#define ASSERT_SOME(container, condition) \
    testpp::internal::Assert::assertAnyOf((container), (condition), __FILE__, __LINE__)

#define ASSERT_NONE(container, condition) \
    testpp::internal::Assert::assertNoneOf((container), (condition), __FILE__, __LINE__)

namespace testpp::internal {
    namespace Assert {
        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertAllOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::allOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertAllOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::allOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertAnyOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::anyOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertAnyOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::anyOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, typename Func>
        requires std::ranges::range<T>
        inline void assertNoneOf(const T& t, const Func& func, const char* file, const int line) {
            auto result = impl_pred::noneOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }

        template <typename T, size_t N, typename Func>
        inline void assertNoneOf(const T(& t)[N], const Func& func, const char* file, const int line) {
            auto result = impl_pred::noneOf(t, func, file, line);
            if (result) {
                Fail::a_fail(*result);
            }
        }
    }
}

#endif
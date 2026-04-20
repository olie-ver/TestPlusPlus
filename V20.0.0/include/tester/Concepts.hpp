#pragma once

#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>

namespace internal {
    namespace Concepts {
        //A concept for types with == defined
        template <typename A, typename B>
        concept HasEQ = requires(A a, B b) {
            { a == b } -> std::convertible_to<bool>;
        };

        //A concept for types with != defined
        template <typename A, typename B>
        concept HasNE = requires(A a, B b) {
            { a != b } -> std::convertible_to<bool>;
        };

        //A concept for types with < defined
        template <typename A, typename B>
        concept HasLT = requires(A a, B b) {
            { a < b } -> std::convertible_to<bool>;
        };

        //A concept for types with <= defined
        template <typename A, typename B>
        concept HasLE = requires(A a, B b) {
            { a <= b } -> std::convertible_to<bool>;
        };

        //A concept for types with > defined
        template <typename A, typename B>
        concept HasGT = requires(A a, B b) {
            { a > b } -> std::convertible_to<bool>;
        };

        //A concept for types with >= defined
        template <typename A, typename B>
        concept HasGE = requires(A a, B b) {
            { a >= b } -> std::convertible_to<bool>;
        };

        //A concept for types that can be nullable
        template <typename A>
        concept Nullable = requires(A a) {
            std::convertible_to<decltype(a == nullptr), bool>;
        };
    }
}

#endif
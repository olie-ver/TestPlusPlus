#pragma once

#ifndef CONCEPTS_H
#define CONCEPTS_H

#include <concepts>
#include <ranges>

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


        //A concept for a common floating point type
        template <typename A, typename B, typename C, typename D>
        concept CommonFloat = requires() {
            std::is_floating_point<std::common_type<A, B, C, D>>::value;
        };

        //A concept for types that are iterable and the types of what they contain are comparable by ==
        template <typename A, typename B>
        concept IterableAndComparable = requires()
        {
            std::ranges::range<A>;
            std::ranges::range<B>;
            HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>;
        };

        //A concept for types that are hashable
        template <typename A>
        concept Hashable = requires(A& a) {
            { std::hash<A>{}(a) } -> std::convertible_to<size_t>;
        };
    }
}

#endif
#pragma once

#ifndef ITER_H
#define ITER_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include <optional>

namespace internal {
    namespace impl_iter {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::Failure> 
        orderedEquals(const A& first, const B& second, const char* file, const int line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::Failure>
        orderedUnequals(const A& first, const B& second, const char* file, const int line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::Failure>
        unorderedEquals(const A& first, const B& second, const char* file, const int line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::Hashable<std::ranges::range_value_t<A>>
            && Concepts::Hashable<std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::Failure> 
        unorderedEqualsHashable(const A& first, const B& second, const char* file, const int line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::HasLT<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::Failure>
        unorderedEqualsLessThan(const A& first, const B& second, const char* file, const int line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline std::optional<Core::Failure> 
        unorderedEqualsGeneral(const A& first, const B& second, const char* file, const int line);

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline std::optional<Core::Failure>
        unorderedUnequals(const A& first, const B& second, const char* file, const int line);

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::Failure>
        empty(const T& container, const char* file, const int line);

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::Failure>
        notEmpty(const T& container, const char* file, const int line);

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::Failure>
        size(const T& container, const size_t size, const char* file, const int line);

        template <typename T, typename U>
        requires std::ranges::range<T>
        inline std::optional<Core::Failure>
        contains(const T& container, const U& find, const char* file, const int line);

        template <typename T, typename U>
        requires std::ranges::range<T>
        inline std::optional<Core::Failure>
        doesNotContain(const T& container, const U& find, const char* file, const int line);
    }
}

#endif
#pragma once

#ifndef TESTPP_CONCEPTS_OPERATORS_H
#define TESTPP_CONCEPTS_OPERATORS_H

#include <concepts>

namespace testpp::internal {
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
    }
}

#endif
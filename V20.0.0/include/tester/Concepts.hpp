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
            { b == a } -> std::convertible_to<bool>;
        };

        //A concept for types with != defined
        template <typename A, typename B>
        concept HasNE = requires(A a, B b) {
            { a != b } -> std::convertible_to<bool>;
            { b != a } -> std::convertible_to<bool>;
        };
    }
}

#endif
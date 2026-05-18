#pragma once

#ifndef FLT_H
#define FLT_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_flt {
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1>
        std::optional<const Core::Failure> 
            absolutelyEqual(A a, B b, T1 abs_tol, const char* file, int line);

        template <typename A, typename B, typename T1, typename T2>
        requires Concepts::CommonFloat<A, B, T1, T2>
        std::optional<const Core::Failure> 
            nearlyEqual(A a, B b, T1 abs_tol, T2 rel_tol, const char* file, int line);
    
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1>
        std::optional<const Core::Failure>
            relativelyEqual(A a, B b, T1 rel_tol, const char* file, int line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::Failure> isNaN(T val, const char* file, int line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::Failure> isNotNaN(T val, const char* file, int line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::Failure> isInf(T val, const char* file, int line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::Failure> isPosInf(T val, const char* file, int line);

        template <typename T>
        requires(std::is_floating_point<T>::value)
        std::optional<const Core::Failure> isNegInf(T val, const char* file, int line);
    }
}

#endif
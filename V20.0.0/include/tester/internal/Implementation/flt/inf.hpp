#pragma once

#ifndef FLT_INF_H
#define FLT_INF_H

#include "../flt.hpp"

namespace internal {
    namespace impl_flt {
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::Failure> 
            isInf(T val, const char* file, int line)
        {
            if (!std::isinf(val)) {
                return Core::Failure({
                    std::string("Expected val to be inf \n      val = " + val),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::Failure> 
            isPosInf(T val, const char* file, int line)
        {
            if (!std::isinf(val)) {
                return Core::Failure({
                    std::string("Expected val to be positive infinity but it wasn't \n      val = " + val),
                    file,
                    line
                });

            } else if (std::isinf(val) && val < 0.0) {
                return Core::Failure({
                    std::string("Expected val to be positive infinity, but it wasn't \n      val = " + val),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::Failure> 
            isNegInf(T val, const char* file, int line)
        {
            if (!std::isinf(val)) {
                return Core::Failure({
                    std::string("Expected val to be negative infinity but it wasn't \n      val = " + val),
                    file,
                    line
                });
            } else if (std::isinf(val) && val > 0.0) {
                return Core::Failure({
                    std::string("Expected val to be negative infinity, but it wasn't \n      val = " + val),
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif
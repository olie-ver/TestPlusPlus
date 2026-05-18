#pragma once

#ifndef FLT_NAN_H
#define FLT_NAN_H

#include "../flt.hpp"

namespace internal {
    namespace impl_flt {
        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::Failure> 
            isNaN(T val, const char* file, int line) 
        {
            if (val != NAN) {
                return Core::Failure({
                    std::string("Expected val to be NaN") + "\n      val = " + val,
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires(std::is_floating_point<T>::value)
        inline std::optional<const Core::Failure> 
            isNotNaN(T val, const char* file, int line)
        {
            if (val != NAN) {
                return Core::Failure({
                    "Expected val to not be NaN \n      val = NaN",
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif
#pragma once

#ifndef NULL_H
#define NULL_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_null {
        template <typename T>
        requires Concepts::Nullable<T>
        inline std::optional<const Core::Failure> 
            Null(const T& val, const char* file, const int line) 
        {
            if (val != nullptr) {
                return Core::Failure({
                    "Expected val to be nullptr.\n val = " + Helpers::toString(val),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires Concepts::Nullable<T>
        inline std::optional<const Core::Failure> 
            NotNull(const T& val, const char* file, const int line)
        {
            if (val == nullptr) {
                return Core::Failure({
                    "Expected val to not be a nullptr.\n val = nullptr ",
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif
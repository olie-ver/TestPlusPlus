#pragma once

#ifndef BOOL_H
#define BOOL_H

#include "../Core.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_bool {
        inline std::optional<const Core::Failure> True(const bool cond, const char* expr,
            const char* file, const int line)
        {
            if (!cond) {
                return Core::Failure("Expected: " + std::string(expr) + " to be true", file, line);
            }
            return std::nullopt;
        }

        inline std::optional<const Core::Failure> False(const bool cond, const char* expr,
            const char* file, const int line)
        {
            if (cond) {
                return Core::Failure("Expected: " + std::string(expr) + " to be false", file, line);
            }
            return std::nullopt;
        }
    }
}

#endif
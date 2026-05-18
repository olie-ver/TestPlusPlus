#pragma once

#ifndef STR_CONT_H
#define STR_CONT_H

#include "../string.hpp"
#include "../../Helpers.hpp"

namespace internal {
    namespace impl_str {
        inline std::optional<const Core::Failure> 
        stringContains(const std::string& first, const std::string& substr,
            const char* file, const int line)
        {
            if (first.find(substr) == std::string::npos) {
                return Core::Failure({
                    std::string("Expected string: " 
                        + first 
                        + " to contain " 
                        + substr 
                        + " but it didn't"
                    ),
                    file,
                    line
                }); 
            }

            return std::nullopt;
        }

        inline std::optional<const Core::Failure>
        stringContains(const char* first, const char* substr, 
            const char* file, const int line)
        {
            bool first_null = first == nullptr;
            bool substr_null = substr == nullptr;

            if (first_null ^ substr_null) {
                return Core::Failure({
                    std::string("Mismatched nullptrs")
                    + "\n    a = nullptr: " + Helpers::toString(first_null)
                    + "\n    b = nullptr:" + Helpers::toString(substr_null),
                    file,
                    line
                });
            }

            return stringContains(std::string(first), std::string(substr), file, line);
        }

        template <size_t N, size_t M>
        inline std::optional<const Core::Failure>
        stringContains(const char(&first)[N], const char(&substr)[M], 
            const char* file, const int line)
        {
            if (N < M) {
                return Core::Failure({
                    "Substring longer than string to check",
                    file,
                    line
                });
            }

            return expectStringContains(std::string(first), std::string(substr), file, line);
        }
    }
}

#endif
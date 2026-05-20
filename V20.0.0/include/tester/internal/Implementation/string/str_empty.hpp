#pragma once

#ifndef STR_EMPTY_H
#define STR_EMPTY_H

#include "../../Core.hpp"
#include "../../Helpers.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_str {
        std::optional<const Core::Failure> 
        inline stringEmpty(std::string& first, const char* file, const int line)
        {
            if (!first.empty()) {
                return Core::Failure({
                    "Expected string to be empty, but wasn't: first = " + first,
                    file,
                    line
                }); 
            }

            return std::nullopt;
        }

        std::optional<const Core::Failure> 
        inline stringEmpty(const char* first, const char* file, const int line)
        {
            if (first == nullptr) {
                return Core::Failure({
                    "nullptr passed in",
                    file,
                    line
                });
            }

            if (first[0] != '\0') {
                return Core::Failure({
                    std::string("Expected string to be empty, but wasn't: first = ") + first,
                    file,
                    line
                }); 
            }

            return std::nullopt;
        }

        template <size_t N>
        std::optional<const Core::Failure> 
        inline stringEmpty(const char(&first)[N], const char* file, const int line)
        {
            if (first[0] != '\0') {
                char a[N + 1];
                std::copy(std::begin(first), std::end(first), std::begin(a));
                a[N] = '\0';
                return Core::Failure({
                    std::string("Expected string to be empty, but wasn't: first = ") + a,
                    file,
                    line
                }); 
            }

            return std::nullopt;
        }

        std::optional<const Core::Failure>
        inline stringNotEmpty(std::string& first, const char* file, const int line)
        {
            if (first.empty()) {
                return Core::Failure({
                    "Expected string to not be empty, but was",
                    file,
                    line
                }); 
            }

            return std::nullopt;
        }

        std::optional<const Core::Failure> 
        inline stringNotEmpty(const char* first, const char* file, const int line)
        {
            if (first == nullptr) {
                return Core::Failure({
                    "nullptr passed in",
                    file,
                    line
                });
            }

            if (first[0] == '\0') {
                return Core::Failure({
                    std::string("Expected string to not be empty, but was"),
                    file,
                    line
                }); 
            }

            return std::nullopt;
        }

        template <size_t N>
        inline std::optional<const Core::Failure> 
        stringNotEmpty(const char(&first)[N], const char* file, const int line)
        {
            if (first[0] == '\0') {
                return Core::Failure({
                    std::string("Expected string to not be empty, but was"),
                    file,
                    line
                }); 
            }
            
            return std::nullopt;
        }
    }
}

#endif
#pragma once

#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <iterator>

#if defined(__clang__) || defined(__GNUG__)
    #include <cxxabi.h>
    #include <cstdlib>
#endif

namespace internal {
    namespace Helpers {
        template <typename T>
        inline auto toStringImpl(const T& value, int) -> decltype(std::declval<std::ostream&>() << value, std::string()) {
            std::ostringstream oss;
            oss << std::fixed << std::setprecision(6) << value;
            return oss.str();
        }

        template <typename T>
        inline std::string toStringImpl(const T&, ...) {
            return "<unprintable>";
        }

        template <typename T>
        inline std::string toString(const T& value) {
            return toStringImpl(value, 0);
        }

        template <typename A, typename B>
        inline std::string toString(const std::pair<A, B>& p) {
            return "(" + toString(p.first) + ", " + toString(p.second) + ")";
        }

        inline std::string demangle(const char* name) {
            #if defined(__clang__) || defined(__GNUG__)
                int status = 0;
                char* demangled = abi::__cxa_demangle(name, nullptr, nullptr, &status);

                std::string result = (status == 0 && demangled) ? demangled : name;

                std::free(demangled);
                return result;
            #else
                // Fallback (MSVC or unknown compiler)
                return name;    
            #endif
        }
    }
}

#endif
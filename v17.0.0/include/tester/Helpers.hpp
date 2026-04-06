#pragma once

#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <sstream>

namespace internal {
    namespace Helpers {
        template <typename T>
        inline auto toStringImpl(const T& value, int) -> decltype(std::declval<std::ostream&>() << value, std::string()) {
            std::ostringstream oss;
            oss << value;
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
    }
}

#endif
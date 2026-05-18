#pragma once

#ifndef ITER_ATTR_H
#define ITER_ATTR_H

#include "../iterable.hpp"

namespace internal {
    namespace impl_iter {
        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::Failure>
        empty(const T& container, const char* file, const int line)
        {
            if (container.size() != 0) {
                return Core::Failure({
                    std::string("Expected container size to be 0, but wasn't. \n" 
                        "     size = " + container.size()),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::Failure>
        notEmpty(const T& container, const char* file, const int line)
        {
            if (container.size() == 0) {
                return Core::Failure({
                    std::string("Expected container size to be positive, but wasn't. \n      size = 0"),
                    file,
                    line
                });
            }
            
            return std::nullopt;
        }

        template <typename T>
        requires Concepts::Sizeable<T>
        inline std::optional<Core::Failure>
        size(const T& container, const size_t size, const char* file, const int line)
        {
            if (container.size() != size) {
                return Core::Failure({
                    std::string("Expected container size to be " 
                        + Helpers::toString(size) + ", but wasn't. \n      size = " 
                        + container.size()),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, typename U>
        requires std::ranges::range<T>
        inline std::optional<Core::Failure>
        contains(const T& container, const U& find, const char* file, const int line)
        {
            static_assert(std::is_same<std::ranges::range_value_t<T>, U>::value);
            auto it = std::find(std::ranges::begin(container), std::ranges::end(container), find);

            if (it == std::ranges::end(container)) {
                return Core::AssertionFailure({
                    std::string("The container did not contain the expected value: " 
                        + Helpers::toString(find)),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename T, typename U>
        requires std::ranges::range<T>
        inline std::optional<Core::Failure>
        doesNotContain(const T& container, const U& find, const char* file, const int line)
        {
            static_assert(std::is_same<std::ranges::range_value_t<T>, U>::value);
            auto it = std::find(std::ranges::begin(container), std::ranges::end(container), find);

            if (it != std::ranges::end(container)) {
                return Core::Failure({
                    std::string("The container did contained the value: " + Helpers::toString(find)),
                    file,
                    line
                });
            }

            return std::nullopt
        }
    }
}

#endif
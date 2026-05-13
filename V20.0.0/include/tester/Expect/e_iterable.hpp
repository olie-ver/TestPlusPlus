#pragma once

#ifndef E_ITER_H
#define E_ITER_H

#include "../Concepts.hpp"
#include "../Helpers.hpp"
#include "../Runner.hpp"
#include <string>
#include <unordered_map>
#include <ranges>

#define EXPECT_ORDERED_EQ(first, second) \
    internal::Expects::expectOrderedEquals((first), (second), __FILE__, __LINE__)
#define EXPECT_UNORDERED_EQ(first, second) \
    internal::Expects::expectUnorderedEquals((first), (second), __FILE__, __LINE__)

#define EXPECT_EMPTY(container) internal::Expects::expectEmpty((container), __FILE__, __LINE__)
#define EXPECT_NEMPTY(container) internal::Expects::expectNotEmpty((container), __FILE__, __LINE__)
#define EXPECT_SIZE(container, size) internal::Expects::expectSize((container), (size), __FILE__, __LINE__)
#define EXPECT_CONTAINS(container, value) internal::Expects::expectContains((container), (value), __FILE__, __LINE__)
#define EXPECT_DOES_NOT_CONTAIN(container, value) \
    internal::Expects::expectDoesNotContain((container), (value), __FILE__, __LINE__)

//Future tests to add: ordered NE, unordered NE, same set (has same elements, regardless of counts), not same set
namespace internal {
    namespace Expects {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectOrderedEquals(const A& first, const B& second, 
            const char* file, const int line)
        {
            namespace ranges = std::ranges;

            auto a_itr = ranges::cbegin(first);
            auto b_itr = ranges::cbegin(second);

            auto a_end = ranges::cend(first);

            size_t size_a = ranges::size(first);
            size_t size_b = ranges::size(second);

            if (size_a != size_b) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Size of collections are not the same\n      Size of first: ") 
                    + Helpers::toString(size_a)
                    + std::string("\n      Size of second: ") + Helpers::toString(size_b),
                    file,
                    line
                });
                return;
            }

            size_t index = 0;

            for (; a_itr != a_end; ++a_itr, ++b_itr, ++index) {
                auto&& a_val = *a_itr;
                auto&& b_val = *b_itr;

                if (!(a_val == b_val)) {
                    std::string idx = Helpers::toString(index);
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Mismatch at index = ") + idx
                        + "\n    a[" + idx + "]: " + Helpers::toString(a_val)
                        + "\n    b[" + idx + "]: " + Helpers::toString(b_val),
                        file,
                        line
                    });
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::Hashable<std::ranges::range_value_t<A>>
            && Concepts::Hashable<std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline void expectUnorderedEqualsHashable(const A& first, const B& second,
            const char* file, const int line) 
        {
            using a_val = std::ranges::range_value_t<A>;
            using b_val = std::ranges::range_value_t<B>;

            using T = std::common_type_t<a_val, b_val>;
            std::unordered_map<T, size_t> counts;

            for (const a_val& a_val : first) {
                counts[a_val]++;
            }

            auto b_itr = std::ranges::cbegin(second);
            auto b_end = std::ranges::cend(second);
            for (; b_itr != b_end; ++b_itr) {
                if (counts[*b_itr] == 0) {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Mismatched element: ") + Helpers::toString(*b_itr),
                        file,
                        line
                    });
                    return;
                } else {
                    counts[*b_itr]--;
                }
            }

            for (const auto& [key, count] : counts) {
                if (count != 0) {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Mismatched element: ") + Helpers::toString(key),
                        file,
                        line
                    });
                    return;
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::HasLT<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline void expectUnorderedEqualsLessThan(const A& first, const B& second,
            const char* file, const int line) 
        {
            using a_val = std::ranges::range_value_t<A>;
            using b_val = std::ranges::range_value_t<B>;

            std::vector<a_val> a_vals(std::ranges::begin(first), std::ranges::end(first));
            std::vector<b_val> b_vals(std::ranges::begin(second), std::ranges::end(second));

            std::sort(a_vals.begin(), a_vals.end());
            std::sort(b_vals.begin(), b_vals.end());

            size_t size = a_vals.size();

            for (size_t i = 0; i < size; i++) {
                if (a_vals[i] != b_vals[i]) {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Mismatched element: ") + Helpers::toString(a_vals[i]),
                        file,
                        line
                    });
                    return;
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline void expectUnorderedEqualsGeneral(const A& first, const B& second,
            const char* file, const int line) 
        {
            //since this function is being called, first and second have the same size
            std::vector<bool> used(std::ranges::size(first));

            auto a_itr = std::ranges::begin(first);

            auto a_end = std::ranges::end(first);
            auto b_end = std::ranges::end(second);

            for (; a_itr != a_end; ++a_itr) {
                size_t idx = 0;
                auto b_itr = std::ranges::begin(second);
                bool found = false;
                for (; b_itr != b_end; ++b_itr, ++idx) {
                    if (*b_itr == *a_itr) {
                        if (!used[idx]) {
                            used[idx] = true;
                            found = true;
                            break;
                        }
                    } 
                }

                if (!found) {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Missing element: ") + Helpers::toString(*a_itr),
                        file,
                        line
                    });
                    return;
                }
            }

            for (size_t i = 0; i < used.size(); i++) {
                if (!used[i]) {
                    Runner::CURRENT_TEST->failures.push_back({
                        "Collections not equivalent",
                        file,
                        line
                    });
                    return;
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectUnorderedEquals(const A& first, const B& second,
            const char* file, const int line) 
        {
            size_t size_a = std::ranges::size(first);
            size_t size_b = std::ranges::size(second);

            if (size_a != size_b) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Size of collections are not the same\n      Size of first: ") 
                    + Helpers::toString(size_a)
                    + std::string("\n      Size of second: ") + Helpers::toString(size_b),
                    file,
                    line
                });
                return;
            }

            using a_val = std::ranges::range_value_t<A>;
            using b_val = std::ranges::range_value_t<B>;

            if constexpr (Concepts::Hashable<a_val> && Concepts::Hashable<b_val> 
                && Concepts::HasEQ<a_val, b_val>)
            {
                expectUnorderedEqualsHashable(first, second, file, line);
            } else if constexpr (Concepts::HasLT<a_val, b_val>) 
            {
                expectUnorderedEqualsLessThan(first, second, file, line);
            } else 
            {
                expectUnorderedEqualsGeneral(first, second, file, line);
            }
        }


        /// @brief An Expects test to check if a container is empty
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void expectEmpty(const T& container, const char* file, const int line) {
            if (container.size() != 0) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected container size to be 0, but wasn't. \n" 
                        + "     size = " + container.size()),
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test to check if a container is empty
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void expectNotEmpty(const T& container, const char* file, const int line) {
            if (container.size() == 0) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected container size to be positive, but wasn't. \n      size = 0"),
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test to check if a container is has a certain size
        /// @tparam T a container that has the .size() method
        /// @param container the container
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T>
        requires Concepts::Sizeable<T>
        inline void expectSize(const T& container, const size_t size, const char* file, const int line) {
            if (container.size() != size) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected container size to be " 
                        + size ", but wasn't. \n      size = " 
                        + container.size()),
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test for seeing if a container contains a value
        /// @tparam T a ranges container
        /// @tparam U the value to be found
        /// @param container a container that fulfills the ranges concept
        /// @param find the value to be found
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T, typename U>
        requires std::ranges::range<T>
        inline void expectContains(const T& container, const U& find, const char* file, const int line) {
            static_assert(std::is_same<std::ranges::range_value_t<T>, U>);
            auto it = std::find(std::ranges::begin(container), std::ranges::end(container), find);

            if (it == std::ranges::end(container)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("The container did not contain the expected value: " + Helpers::ToString(find)),
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test for seeing if a container does not contain a value
        /// @tparam T a ranges container
        /// @tparam U the value to be found
        /// @param container a container that fulfills the ranges concept
        /// @param find the value to be found
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <typename T, typename U>
        requires std::ranges::range<T>
        inline void expectDoesNotContain(const T& container, const U& find, const char* file, const int line) {
            static_assert(std::is_same<std::ranges::range_value_t<T>, U>);
            auto it = std::find(std::ranges::begin(container), std::ranges::end(container), find);

            if (it != std::ranges::end(container)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("The container did contained the value: " + Helpers::ToString(find)),
                    file,
                    line
                });
            }
        }
    }
}

#endif
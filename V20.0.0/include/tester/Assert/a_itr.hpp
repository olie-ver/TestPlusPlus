#pragma once

#ifndef A_ITR_H
#define A_ITR_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include "../Helpers.hpp"
#include "../Runner.hpp"
#include <string>
#include <unordered_map>
#include <ranges>

#define ASSERT_ORDERED_EQ(first, second) \
    internal::Assert::assertOrderedEquals((first), (second), __FILE__, __LINE__)
#define ASSERT_UNORDERED_EQ(first, second) \
    internal::Assert::assertUnorderedEquals((first), (second), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertOrderedEquals(const A& first, const B& second, 
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
                throw Core::AssertionFailure();
            }

            size_t index = 0;

            bool failed = false;

            for (; a_itr != a_end; ++a_itr, ++b_itr, ++index) {
                auto&& a_val = *a_itr;
                auto&& b_val = *b_itr;

                if (!(a_val == b_val)) {
                    failed = true;
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

            if (failed) {
                throw Core::AssertionFailure();
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::Hashable<std::ranges::range_value_t<A>>
            && Concepts::Hashable<std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline void assertUnorderedEqualsHashable(const A& first, const B& second,
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
                    throw Core::AssertionFailure();
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
                    throw Core::AssertionFailure();
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B> 
            && Concepts::HasLT<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline void assertUnorderedEqualsLessThan(const A& first, const B& second,
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
                    throw Core::AssertionFailure();
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
            && Concepts::HasEQ<std::ranges::range_value_t<A>, std::ranges::range_value_t<B>>
        inline void assertUnorderedEqualsGeneral(const A& first, const B& second,
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
                    throw Core::AssertionFailure();
                }
            }

            for (size_t i = 0; i < used.size(); i++) {
                if (!used[i]) {
                    Runner::CURRENT_TEST->failures.push_back({
                        "Collections not equivalent",
                        file,
                        line
                    });
                    throw Core::AssertionFailure();
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void assertUnorderedEquals(const A& first, const B& second,
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
                throw Core::AssertionFailure();
            }

            using a_val = std::ranges::range_value_t<A>;
            using b_val = std::ranges::range_value_t<B>;

            if constexpr (Concepts::Hashable<a_val> && Concepts::Hashable<b_val> 
                && Concepts::HasEQ<a_val, b_val>)
            {
                assertUnorderedEqualsHashable(first, second, file, line);
            } else if constexpr (Concepts::HasLT<a_val, b_val>) 
            {
                assertUnorderedEqualsLessThan(first, second, file, line);
            } else 
            {
                assertUnorderedEqualsGeneral(first, second, file, line);
            }
        }
    }
}

#endif
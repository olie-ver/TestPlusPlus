#pragma once

#ifndef E_ITER_H
#define E_ITER_H

#include "../Runner.hpp"
#include "../Helpers.hpp"
#include <sstream>
#include <type_traits>
#include <iterator>

#define EXPECT_EQ_ORDERED(first, second) internal::Expect::expectOrderedRangeEq((first), (second), __FILE__, __LINE__)

namespace internal {
    namespace Expect {

        template <typename T, size_t N>
        inline void expectOrderedRangeEq(T(& first)[N], T(& second)[N], const char* file, int line) {
            std::stringstream stream;
            bool mismatch = false;
            for (size_t i = 0; i < N; i++) {
                if (!(first[i] == second[i])) {
                    stream << "     Mismatched element at index " << i;
                    stream << "\n     first[" << i << "]: " << Helpers::toString(first[i]);
                    stream << "\n     second[" << i << "]: " << Helpers::toString(second[i]);
                    mismatch = true;
                }
            }

            if (mismatch) {
                Runner::CURRENT_TEST->failures.push_back({
                    stream.str(),
                    file,
                    line
                });
            }
        }

        template <typename A, typename B,
          std::enable_if_t<Helpers::are_iterables_comparable<A, B>::value, int> = 0>
        inline void expectOrderedRangeEq(const A& a, const B& b, const char* file, int line)
        {
            auto a_itr = std::begin(a);
            auto b_itr = std::begin(b);

            auto a_end = std::end(a);
            auto b_end = std::end(b);
            if (std::distance(a_itr, a_end) != std::distance(b_itr, b_end)) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Size of collections are not the same",
                    file,
                    line
                });
                return;
            }
            size_t index = 0;
            for (; a_itr != a_end; ++a_itr, ++b_itr, ++index)
            {
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
    }
}

#endif
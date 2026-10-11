#pragma once

#ifndef A_MULTIPLE_H
#define A_MULTIPLE_H

#include <functional>

#define ASSERT_FOR(idx, begin, end, update) testpp::internal::Assert::assert_for((long idx), (begin), (end), ([&idx]() {update;}), ([&idx]() {}))

namespace testpp::internal {
    namespace Assert {
        template <typename T>
        inline void assert_for(long idx, const long begin, const long end, const std::function<long()> update) {
            for (idx = begin; begin != end; update()) 
        }
    }
}

int main() {
    // ASSERT_FOR(hi, 0, 5, hi++) {

    // }

    // long hi;

    // testpp::internal::Assert::assert_for((hi), (0), (5), ([&hi]() {hi++;})) ([&hi]() {});
}

#endif
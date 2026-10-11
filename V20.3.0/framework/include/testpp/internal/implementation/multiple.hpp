#pragma once

#ifndef MULTIPLE_H
#define MULTIPLE_H

#include "../core/core.hpp"

#define ASSERT_FOR(begin, end, update, body) testpp::internal::impl_multiple::runAssertFor((begin), (end), (update), (body))

namespace testpp::internal {
    namespace impl_multiple {
        
        template <typename Begin, typename End, typename Update, typename Body>
        void runAssertFor(Begin begin, End end, Update update, Body body) {
            FailureCollector collector;
            FailureScope scope(collector);

            std::size_t iteration = 0;

            for (auto i = begin; i != end; update(i)) {
                collector.iteration = iteration++;

                try {
                    body(i);
                } catch (const Core::AssertionFailure&) {
                    break;
                }
            }

            // Transfer collected failures to TEST_STACK here.
            // If failures exist, propagate AssertionFailure after
            // the collector has been finalized.
        }

    }
}

// int main() {
//     ASSERT_FOR(0, 5, ++, )
// }

#endif
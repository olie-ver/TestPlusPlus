#pragma once

#ifndef MULTIPLE_H
#define MULTIPLE_H

#include "../core/core.hpp"
#include "../runner.hpp"

namespace testpp::internal {
    namespace impl_multiple {
        std::deque<std::pair<Core::FailureInfo, size_t>> testFor(long long& idx, const long long& end, 
            const std::function<void()>& update, const std::function<void()>& func)
        {
            Runner::NESTED_COLLECT = true;
            std::deque<std::pair<Core::FailureInfo, size_t>> failures;

            for (; idx != end; update()) {
                size_t iteration = idx;
                try {
                    func();
                } catch (const Core::AssertionFailure& failure) {
                    failures.push_back(std::pair<Core::FailureInfo, size_t>(failure.info, iteration));
                    if (failure.stop) {
                        break;
                    }
                }
            }

            Runner::NESTED_COLLECT = false;

            return failures;
        }

    }
}

#endif
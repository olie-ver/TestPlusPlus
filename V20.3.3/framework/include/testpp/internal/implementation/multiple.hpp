#pragma once

#ifndef MULTIPLE_H
#define MULTIPLE_H

#include "../core/core.hpp"
#include "../concepts/has_quality.hpp"
#include "../runner.hpp"

namespace testpp::internal {
    namespace impl_multiple {
        template <typename A>
        std::deque<std::pair<Core::FailureInfo, size_t>> testFor(long long& idx, const long long& end, 
            const std::function<void()>& update, A&& func)
        {
            Runner::NESTED_COLLECT = true;
            std::deque<std::pair<Core::FailureInfo, size_t>> failures;

            for (; idx != end; update()) {
                size_t iteration = idx;
                try {
                    // std::cout << std::to_string(idx) << std::endl;
                    func();
                } catch (const Core::AssertionFailure& failure) {
                    failures.push_back(std::pair<Core::FailureInfo, size_t>(failure.info, iteration));
                    if (failure.stop) {
                        break;
                    }
                } catch (...) {
                    Runner::NESTED_COLLECT = false;
                    throw std::domain_error("Unexpected exception thrown in ASSERT_FOR() or EXPECT_FOR()");
                }
            }

            Runner::NESTED_COLLECT = false;

            return failures;
        }

        template <typename A>
        using ForEachFailures = std::deque<std::pair<Core::FailureInfo, std::ranges::range_value_t<A>>>;

        template <typename A, typename B>
        requires Concepts::Iterable<A>
        ForEachFailures<A> testForEach(const A& container, B&& func) {
            using a_val = std::ranges::range_value_t<A>;

            Runner::NESTED_COLLECT = true;
            ForEachFailures<A> failures;

            for (const auto& val : container) {
                try {
                    // std::cout << std::to_string(val) << std::endl;
                    func(val);
                } catch (const Core::AssertionFailure& failure) {
                    failures.push_back(std::pair<Core::FailureInfo, a_val>(failure.info, val));
                    if (failure.stop) {
                        break;
                    }
                } catch (...) {
                    Runner::NESTED_COLLECT = false;
                    throw std::domain_error("Unexpected exception thrown in ASSERT_EACH() or EXPECT_EACH()");
                }
            }

            Runner::NESTED_COLLECT = false;

            return failures;
        }

        template <typename A, typename B, typename C>
        std::deque<std::pair<Core::FailureInfo, A>> testWhile(A& val, B&& cond, C&& func) {
            Runner::NESTED_COLLECT = true;

            std::deque<std::pair<Core::FailureInfo, A>> failures;
            while (cond()) {
                try {
                    // std::cout << "val = " << std::to_string(val) << std::endl;
                    func();
                } catch (const Core::AssertionFailure& failure) {
                    failures.push_back(std::pair<Core::FailureInfo, A>(failure.info, val));
                    if (failure.stop) {
                        break;
                    }
                } catch (...) {
                    Runner::NESTED_COLLECT = false;
                    throw std::domain_error("Unexpected exception thrown in ASSERT_EACH() or EXPECT_EACH()");
                }
            }

            Runner::NESTED_COLLECT = false;
            return failures;
        }
    }
}

#endif
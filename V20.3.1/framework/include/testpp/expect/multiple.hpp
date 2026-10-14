#pragma once

#ifndef E_MULTIPLE_H
#define E_MULTIPLE_H

#include "../internal/implementation/multiple.hpp"

#include <functional>
#include <sstream>

#define EXPECT_FOR(idx, begin, end, update, func) \
    { \
        long long idx = (begin); \
        testpp::internal::Expect::expect_for(__FILE__, __LINE__, (idx), (end), [&idx](){ update; }, [&]() func); \
    }

#define EXPECT_EACH(value, container, func) \
    testpp::internal::Expect::expect_for_each(__FILE__, __LINE__, (container), [&](const auto& value) func)

#define EXPECT_WHILE(value, initial, condition, func) \
    { \
        auto value = (initial); \
        testpp::internal::Expect::expect_while(__FILE__, __LINE__, value, [&value](){ return condition; }, [&]() func); \
    }

namespace testpp::internal {
    namespace Expect {
        inline void expect_for(const char* file, const uint32_t line, long long& idx, 
            const long long& end, const std::function<void()>& update, const std::function<void()>& func)
        {
            std::deque<std::pair<Core::FailureInfo, size_t>> failures = std::move(impl_multiple::testFor(idx, end, update, func));

            if (failures.size()) {
                Core::FailureInfo fail("", file, line, "", "", "");

                std::stringstream stream;
                stream << "\nFailed " << std::to_string(failures.size()) << " times:";

                fail.message = stream.str();

                stream.str("");
                stream.clear();

                std::vector<Core::FailureInfo> fails;
                fails.reserve(failures.size() + 1);
                fails.push_back(std::move(fail));

                for (size_t i = 0; i < failures.size(); i++) {
                    auto& fail_pair = failures[i];
                    stream << "Failed with idx = " << std::to_string(fail_pair.second) << '\n';
                    stream << '\t' << fail_pair.first.message;
                    fail_pair.first.message = stream.str();

                    stream.str("");
                    stream.clear();

                    fails.push_back(std::move(fail_pair.first));
                }

                Fail::e_fail(fails);
            }
        }

        template <typename A, typename B>
        requires Concepts::Iterable<A>
        inline void expect_for_each(const char* file, const uint32_t line, const A& container, B&& func) {
            using a_val = std::ranges::range_value_t<A>;
            std::deque<std::pair<Core::FailureInfo, a_val>> failures = std::move(impl_multiple::testForEach(container, func));

            if (failures.size()) {
                Core::FailureInfo fail("", file, line, "", "", "");

                std::stringstream stream;
                stream << "\nFailed " << std::to_string(failures.size()) << " times:";

                fail.message = stream.str();

                stream.str("");
                stream.clear();

                std::vector<Core::FailureInfo> fails;
                fails.reserve(failures.size() + 1);
                fails.push_back(std::move(fail));

                for (size_t i = 0; i < failures.size(); i++) {
                    auto& fail_pair = failures[i];
                    stream << "Failed with value = " << std::to_string(fail_pair.second) << '\n';
                    stream << '\t' << fail_pair.first.message;
                    fail_pair.first.message = stream.str();

                    stream.str("");
                    stream.clear();

                    fails.push_back(std::move(fail_pair.first));
                }

                Fail::e_fail(fails);
            }
        }

        template <typename A, typename B, typename C>
        inline void expect_while(const char* file, const uint32_t line, A& initial, B&& cond, C&& func) {
            std::deque<std::pair<Core::FailureInfo, A>> failures = std::move(impl_multiple::testWhile(initial, cond, func));
            
            if (failures.size()) {
                Core::FailureInfo fail("", file, line, "", "", "");

                std::stringstream stream;
                stream << "\nFailed " << std::to_string(failures.size()) << " times:";

                fail.message = stream.str();

                stream.str("");
                stream.clear();

                std::vector<Core::FailureInfo> fails;
                fails.reserve(failures.size() + 1);
                fails.push_back(std::move(fail));

                for (size_t i = 0; i < failures.size(); i++) {
                    auto& fail_pair = failures[i];
                    stream << "Failed with value = " << std::to_string(fail_pair.second) << '\n';
                    stream << '\t' << fail_pair.first.message;
                    fail_pair.first.message = stream.str();

                    stream.str("");
                    stream.clear();

                    fails.push_back(std::move(fail_pair.first));
                }

                Fail::e_fail(fails);
            }
        }
    }
}



#endif
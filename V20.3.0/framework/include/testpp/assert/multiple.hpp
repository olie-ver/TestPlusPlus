#pragma once

#ifndef A_MULTIPLE_H
#define A_MULTIPLE_H

#include "../internal/implementation/multiple.hpp"

#include <functional>
#include <sstream>

#define ASSERT_FOR(idx, begin, end, update, func) \
    long long idx = begin; \
    testpp::internal::Assert::assert_for(__FILE__, __LINE__, (idx), (end), [&idx](){ update; }, [&]() func);

namespace testpp::internal {
    namespace Assert {
        inline void assert_for(const char* file, const uint32_t line, long long& idx, 
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

                Fail::a_fail(fails);
            }
        }
    }
}



#endif
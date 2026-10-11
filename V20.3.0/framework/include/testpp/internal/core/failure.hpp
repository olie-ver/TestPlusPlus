#pragma once

#ifndef TESTPP_CORE_FAILURE_H
#define TESTPP_CORE_FAILURE_H

#include "core.hpp"

#include <vector>

namespace testpp::internal {
    namespace Core {
        struct CollectedFailure {
            FailureInfo failure;
            std::size_t iteration;
        };

        class FailureCollector {
            public:
                std::vector<CollectedFailure> failures;
                std::size_t iteration = 0;

                void record(const FailureInfo& failure) {
                    failures.push_back({failure, iteration});
                }

                bool failed() const {
                    return !failures.empty();
                }

            private:
        };


        inline thread_local std::vector<Core::FailureCollector*> FAILURE_SCOPES{};

        inline FailureCollector* currentCollector() {
            if (FAILURE_SCOPES.empty()) {
                return nullptr;
            }
            return FAILURE_SCOPES.back();
        }

        class FailureScope {
            public:
                explicit FailureScope(FailureCollector& collector) : collector(collector) {
                    FAILURE_SCOPES.push_back(&collector);
                }

                ~FailureScope() {
                    FAILURE_SCOPES.pop_back();
                }

                FailureScope(const FailureScope&) = delete;
                FailureScope& operator=(const FailureScope&) = delete;

            private:
                FailureCollector& collector;
        };
    }
}

#endif
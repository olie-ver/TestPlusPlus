#pragma once

#ifndef FAIL_H
#define FAIL_H

#include "core/core.hpp"
#include "core/failure.hpp"
#include "runner.hpp"

namespace testpp::internal {
    namespace Fail {
        inline void e_fail(const Core::FailureInfo& result) {
            if (!Runner::NESTED_COLLECT) {
                Runner::TEST_STACK.back().failures.push_back(result);
            } else {
                Core::AssertionFailure failure;
                failure.info = result;
                failure.stop = false;
                throw failure;
            }
        }

        inline void e_fail(const std::vector<Core::FailureInfo>& failures) {
            for (size_t i = 0; i < failures.size(); i++) {
                Runner::TEST_STACK.back().failures.push_back(failures[i]);
            }
        }

        inline void a_fail(const Core::FailureInfo& result) {
            if (!Runner::NESTED_COLLECT) {
                Runner::TEST_STACK.back().failures.push_back(result);
            }

            Core::AssertionFailure failure;
            failure.info = result;
            failure.stop = true;

            throw failure;
        }

        inline void a_fail(const std::vector<Core::FailureInfo>& failures) {
            for (size_t i = 0; i < failures.size(); i++) {
                Runner::TEST_STACK.back().failures.push_back(failures[i]);
            }

            throw Core::AssertionFailure();
        }
    }
}

#endif
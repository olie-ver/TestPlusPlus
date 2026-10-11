#pragma once

#ifndef FAIL_H
#define FAIL_H

#include "core/core.hpp"
#include "core/failure.hpp"
#include "runner.hpp"

namespace testpp::internal {
    namespace Fail {
        inline void e_fail(const Core::FailureInfo& result) {
            if (auto* collector = Core::currentCollector()) {
                collector->record(result);
                return;
            }

            Runner::TEST_STACK.back().failures.push_back(result);
        }

        inline void a_fail(const Core::FailureInfo& result) {
            if (auto* collector = Core::currentCollector()) {
                collector->record(result);
                throw Core::AssertionFailure();
            }

            Runner::TEST_STACK.back().failures.push_back(result);
            throw Core::AssertionFailure();
        }
    }
}

#endif
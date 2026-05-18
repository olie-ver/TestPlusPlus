#pragma once

#ifndef FAIL_H
#define FAIL_H

#include "Core.hpp"
#include "Runner.hpp"

namespace internal {
    namespace Fail {
        inline void e_fail(const Core::Failure& result) {
            Runner::CURRENT_TEST->failures.push_back(result);
        }

        inline void a_fail(const Core::Failure& result) {
            Runner::CURRENT_TEST->failures.push_back(result);
            throw Core::AssertionFailure();
        }
    }
}

#endif
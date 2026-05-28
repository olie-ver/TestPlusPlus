#pragma once

#ifndef TIMING_H
#define TIMING_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

namespace internal {
    namespace impl_iso {
        inline std::optional<Core::FailureInfo> 
        timeout() {
            return std::nullopt;
        }

        inline std::optional<Core::FailureInfo> 
        completesWithin() {
            return std::nullopt;
        }

        inline std::optional<Core::FailureInfo> 
        deadlock() {
            return std::nullopt;
        }
    }
}

#endif
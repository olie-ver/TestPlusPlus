#pragma once

#ifndef TIMING_H
#define TIMING_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "isolation_unix.hpp"

namespace internal {
    namespace impl_iso {
        std::optional<const Core::FailureInfo> 
        timeout() {

        }

        std::optional<const Core::FailureInfo> 
        completesWithin() {

        }

        std::optional<const Core::FailureInfo> 
        deadlock() {
            
        }
    }
}

#endif
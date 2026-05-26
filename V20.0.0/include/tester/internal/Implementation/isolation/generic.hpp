#pragma once

#ifndef GENERIC_H
#define GENERIC_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "isolation_unix.hpp"

namespace internal {
    namespace impl_iso {
        std::optional<const Core::FailureInfo> 
        processResult() {

        }

        std::optional<const Core::FailureInfo> 
        terminationSignal() {

        }

        std::optional<const Core::FailureInfo> 
        processKilled() {

        }

        std::optional<const Core::FailureInfo> 
        coreDumped() {
            
        }
    }
}

#endif
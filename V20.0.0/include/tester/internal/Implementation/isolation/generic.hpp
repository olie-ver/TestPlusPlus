#pragma once

#ifndef GENERIC_H
#define GENERIC_H

#include "../isolation.hpp"

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
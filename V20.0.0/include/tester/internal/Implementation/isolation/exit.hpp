#pragma once

#ifndef EXIT_H
#define EXIT_H

#include "../isolation.hpp"

namespace internal {
    namespace impl_iso {
        std::optional<const Core::FailureInfo> 
        success() {

        }

        std::optional<const Core::FailureInfo> 
        failure() {

        }

        std::optional<const Core::FailureInfo> 
        nonzeroExit() {

        }

        std::optional<const Core::FailureInfo> 
        exitCode() {

        }

        std::optional<const Core::FailureInfo> 
        completes() {
            
        }
    }
}

#endif
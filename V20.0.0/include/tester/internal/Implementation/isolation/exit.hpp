#pragma once

#ifndef EXIT_H
#define EXIT_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "isolation_unix.hpp"

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
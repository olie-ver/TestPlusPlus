#pragma once

#ifndef OUTPUT_H
#define OUPUT_H

#include "../isolation.hpp"

namespace internal {
    namespace impl_iso {
        std::optional<const Core::FailureInfo> 
        stdoutContains() {
            
        }

        std::optional<const Core::FailureInfo> 
        stderrContains() {

        }

        std::optional<const Core::FailureInfo> 
        noStderr() {

        }

        std::optional<const Core::FailureInfo> 
        noStdout() {

        }

        std::optional<const Core::FailureInfo> 
        outputMatches() {

        }
    }
}

#endif
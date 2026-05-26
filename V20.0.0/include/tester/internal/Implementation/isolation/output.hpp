#pragma once

#ifndef OUTPUT_H
#define OUPUT_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

namespace internal {
    namespace impl_iso {
        inline std::optional<const Core::FailureInfo> 
        stdoutContains() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        stderrContains() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        noStderr() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        noStdout() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        outputMatches() {
            return std::nullopt;
        }
    }
}

#endif
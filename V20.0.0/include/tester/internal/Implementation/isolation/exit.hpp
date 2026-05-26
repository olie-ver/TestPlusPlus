#pragma once

#ifndef EXIT_H
#define EXIT_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"

namespace internal {
    namespace impl_iso {
        inline std::optional<const Core::FailureInfo> 
        success() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        failure() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        nonzeroExit() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        exitCode() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        completes() {
            return std::nullopt;
        }
    }
}

#endif
#pragma once

#ifndef GENERIC_H
#define GENERIC_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

namespace internal {
    namespace impl_iso {
        inline std::optional<Core::FailureInfo> 
        processResult() {
            return std::nullopt;
        }

        inline std::optional<Core::FailureInfo> 
        terminationSignal() {
            return std::nullopt;
        }

        inline std::optional<Core::FailureInfo> 
        processKilled() {
            return std::nullopt;
        }

        inline std::optional<Core::FailureInfo> 
        coreDumped() {
            return std::nullopt;
        }
    }
}

#endif
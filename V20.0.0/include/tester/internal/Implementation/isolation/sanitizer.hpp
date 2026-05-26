#pragma once

#ifndef SANITIZER_H
#define SANITIZER_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

namespace internal {
    namespace impl_iso {
        inline std::optional<const Core::FailureInfo> 
        asanFailure() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        ubsanFailure() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        tsanFailure() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        lsanFailure() {
            return std::nullopt;
        }
    }
}

#endif
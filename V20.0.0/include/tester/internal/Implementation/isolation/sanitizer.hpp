#pragma once

#ifndef SANITIZER_H
#define SANITIZER_H

#include "../isolation.hpp"

namespace internal {
    namespace impl_iso {
        std::optional<const Core::FailureInfo> 
        asanFailure() {

        }

        std::optional<const Core::FailureInfo> 
        ubsanFailure() {

        }

        std::optional<const Core::FailureInfo> 
        tsanFailure() {

        }

        std::optional<const Core::FailureInfo> 
        lsanFailure() {
            
        }
    }
}

#endif
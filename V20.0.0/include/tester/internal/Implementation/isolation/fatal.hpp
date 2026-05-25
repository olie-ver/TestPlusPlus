#pragma once

#ifndef FATAL_H
#define FATAL_H

#include "../isolation.hpp"

namespace internal {
    namespace impl_iso {
        std::optional<const Core::FailureInfo> 
        death() {

        }

        std::optional<const Core::FailureInfo> 
        segfault() {

        }

        std::optional<const Core::FailureInfo> 
        abort() {

        }

        std::optional<const Core::FailureInfo> 
        fatal() {

        }

        std::optional<const Core::FailureInfo> 
        nonFatal() {

        }
    }
}

#endif
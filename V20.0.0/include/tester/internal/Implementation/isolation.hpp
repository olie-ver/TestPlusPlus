#pragma once

#ifndef ISO_H
#define ISO_H

#include "../Core.hpp"
#include "isolation_types.hpp"

#include <optional>
#include <string>

namespace internal {
    namespace impl_iso {
        // ============================================================
        // Crash / Fatal Behavior Assertions
        // ============================================================
        template<typename Func>
        std::optional<const Core::FailureInfo> 
        death(Func&& func);

        std::optional<const Core::FailureInfo> 
        segfault();

        std::optional<const Core::FailureInfo> 
        abort();

        //"Bad thing tests"
        std::optional<const Core::FailureInfo> 
        fatal();

        std::optional<const Core::FailureInfo> 
        nonFatal();

        // ============================================================
        // Process Exit Assertions
        // ============================================================

        std::optional<const Core::FailureInfo> 
        success();

        std::optional<const Core::FailureInfo> 
        failure();

        std::optional<const Core::FailureInfo> 
        nonzeroExit();

        std::optional<const Core::FailureInfo> 
        exitCode();

        std::optional<const Core::FailureInfo> 
        completes();

        // ============================================================
        // Output Assertions
        // ============================================================

        std::optional<const Core::FailureInfo> 
        stdoutContains();

        std::optional<const Core::FailureInfo> 
        stderrContains();

        std::optional<const Core::FailureInfo> 
        noStderr();

        std::optional<const Core::FailureInfo> 
        noStdout();

        std::optional<const Core::FailureInfo> 
        outputMatches();

        // ============================================================
        // Sanitizer Assertions
        // ============================================================

        std::optional<const Core::FailureInfo> 
        asanFailure();

        std::optional<const Core::FailureInfo> 
        ubsanFailure();

        std::optional<const Core::FailureInfo> 
        tsanFailure();

        std::optional<const Core::FailureInfo> 
        lsanFailure();

        // ============================================================
        // Timing / Concurrency Assertions
        // ============================================================

        std::optional<const Core::FailureInfo> 
        timeout();

        std::optional<const Core::FailureInfo> 
        completesWithin();

        std::optional<const Core::FailureInfo> 
        deadlock();

        // ============================================================
        // Generic / Advanced Assertions
        // ============================================================

        std::optional<const Core::FailureInfo> 
        processResult();

        std::optional<const Core::FailureInfo> 
        terminationSignal();

        std::optional<const Core::FailureInfo> 
        processKilled();

        std::optional<const Core::FailureInfo> 
        coreDumped();
    }
}

#include "isolation/exit.hpp"
#include "isolation/fatal.hpp"
#include "isolation/generic.hpp"
#include "isolation/output.hpp"
#include "isolation/sanitizer.hpp"
#include "isolation/timing.hpp"

#endif
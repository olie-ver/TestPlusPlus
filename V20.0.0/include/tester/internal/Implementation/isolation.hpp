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

        //fails if Execution Status != Completed
        template<typename Func> 
        Core::ExecutionResult death(Func&& func);

        //passes if Crash Type == SegmentationFault
        template<typename Func> 
        Core::ExecutionResult segfault(Func&& func);

        //Passes if Crash Type == Abort
        template<typename Func> 
        Core::ExecutionResult abort(Func&& func);

        //"Bad thing tests"
        //Passes if something fatal happens
        template<typename Func> 
        Core::ExecutionResult fatal(Func&& func);

        //Passes if nothing fatal happens
        template<typename Func> 
        Core::ExecutionResult nonFatal(Func&& func);

        // ============================================================
        // Process Exit Assertions
        // ============================================================

        //Passes if exit code == EXIT_SUCCESS
        template<typename Func> 
        Core::ExecutionResult success(Func&& func);

        //Passes if exit code == EXIT_FAILURE
        template<typename Func> 
        Core::ExecutionResult failure(Func&& func);

        //Passes if exit code != 0
        template<typename Func> 
        Core::ExecutionResult nonzeroExit(Func&& func);

        //Passes if exit code == (param) exit code
        template<typename Func> 
        Core::ExecutionResult exitCode(Func&& func);

        //Passes if Execution Status == Completed
        template<typename Func> 
        Core::ExecutionResult completes(Func&& func);

        // ============================================================
        // Output Assertions
        // ============================================================

        //Passes if stdout output contains (param) string
        template<typename Func> 
        inline Core::ExecutionResult stdoutContains(Func&& func);

        //Passes if stderr output contains (param) string
        template<typename Func> 
        inline Core::ExecutionResult stderrContains(Func&& func);

        //Passes if there is no stderr output
        template<typename Func> 
        inline Core::ExecutionResult noStdout(Func&& func);

        //Passes if there is no stdout output
        template<typename Func> 
        inline Core::ExecutionResult noStderr(Func&& func);

        //Passes if output == (param) output
        template<typename Func> 
        inline Core::ExecutionResult stdoutMatches(Func&& func);

        //Passes if output == (param) output
        template<typename Func> 
        inline Core::ExecutionResult stderrMatches(Func&& func);

        // ============================================================
        // Sanitizer Assertions
        // ============================================================

        template<typename Func> 
        inline Core::ExecutionResult asanFailure(Func&& func);

        template<typename Func> 
        inline Core::ExecutionResult ubsanFailure(Func&& func);

        template<typename Func> 
        inline Core::ExecutionResult tsanFailure(Func&& func);

        template<typename Func> 
        inline Core::ExecutionResult lsanFailure(Func&& func);

        // ============================================================
        // Timing / Concurrency Assertions
        // ============================================================

        //Passes if it runs longer than the passed in timeout
        std::optional<Core::FailureInfo> 
        timeout();

        //Passes if it runs shorter than the passed in timeout
        std::optional<Core::FailureInfo> 
        completesWithin();

        //Passes if there is a deadlock (inspect thread states?)
        std::optional<Core::FailureInfo> 
        deadlock();

        // ============================================================
        // Generic / Advanced Assertions
        // ============================================================

        //Passes if the process result == (param) result
        std::optional<Core::FailureInfo> 
        processResult();

        //Passes if the termination signal == (param) termination signal
        std::optional<Core::FailureInfo> 
        terminationSignal();

        //Passes if the process was killed
        std::optional<Core::FailureInfo> 
        processKilled();

        //Passes if the core was dumped
        std::optional<Core::FailureInfo> 
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
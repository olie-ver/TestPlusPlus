#pragma once

#ifndef FATAL_H
#define FATAL_H

#include "../../Core.hpp"
#include "../../Concepts.hpp"
#include "../../Helpers.hpp"
#include "../isolation_types.hpp"

#include <iostream>

namespace internal {
    namespace impl_iso {
        template<typename Func>
        inline std::optional<const Core::FailureInfo> 
        death(Func&& func) {
            IsolationRun result = isolateRun(func);
            std::cout << "Execution status: " << Core::ExecutionStrings[(int)result.execution_status] << std::endl;
            std::cout << "Child pid: " << result.child_process_id << std::endl;
            std::cout << "Native exit code: " << result.native_exit_code << std::endl;
            std::cout << "Native signal " << result.native_signal << std::endl;
            std::cout << "Crash type: " << Core::CrashStrings[(int)result.crash_type] << std::endl;
            std::cout << "Duration (ms): " << result.duration_ms << std::endl;
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        segfault() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        abort() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        fatal() {
            return std::nullopt;
        }

        inline std::optional<const Core::FailureInfo> 
        nonFatal() {
            return std::nullopt;
        }
    }
}

#endif
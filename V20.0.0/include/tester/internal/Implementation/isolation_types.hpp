#pragma once

#ifndef ISO_TYPE_H
#define ISO_TYPE_H

#include "../Core.hpp"

namespace internal {
    namespace impl_iso {
        struct IsolationRun {
            Core::ExecutionStatus execution_status;
            pid_t child_process_id;
            int native_exit_code;
            int native_signal;
            Core::CrashType crash_type = Core::CrashType::None;
            int duration_ms;
        };

        //The definition all platforms must implement to 
        //  be able to run tests in isolation
        IsolationRun runIsolatedImpl(const std::function<void()>& func);

        /// @brief The core behind running an isolated test
        /// @tparam Func a function to run
        /// @param func the function to run
        /// @return a TestExecutionResult
        template<typename Func>
        inline IsolationRun isolateRun(Func&& func)
        {
            return internal::impl_iso::runIsolatedImpl(
                std::function<void()>(
                    std::forward<Func>(func)
                )
            );
        }
    }
}

#endif
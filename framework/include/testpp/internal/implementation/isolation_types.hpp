#pragma once

#ifndef ISO_TYPE_H
#define ISO_TYPE_H


#pragma once

#include "../core/core.hpp"
#include "../core/isolated.hpp"

#include <functional>
#include <utility>

namespace testpp::internal {
    namespace impl_iso {

    inline constexpr int DEFAULT_ISOLATION_TIMEOUT_MS = 10000;

    #ifdef _WIN32

        // Implemented by the Windows process launcher.
        Core::ExecutionResult runIsolatedImpl(
            std::size_t testIndex,
            std::size_t isolationIndex,
            int timeLimitMs
        );

        template<typename Func>
        inline Core::ExecutionResult runIsolated(Func&& func, int timeLimitMs = DEFAULT_ISOLATION_TIMEOUT_MS) {
            auto& ctx = Runner::getDeathContext();
            const std::size_t isolationIndex = ctx.currentIsolation++;

            if (ctx.childMode) {
                if (Runner::TEST_STACK.back().idx == ctx.targetTest &&
                    isolationIndex == ctx.targetIndex) {
                    std::forward<Func>(func)();
                }

                return {};
            }

            return runIsolatedImpl(
                Runner::TEST_STACK.back().idx,
                isolationIndex,
                timeLimitMs
            );
        }

    #else

        Core::ExecutionResult runIsolatedImpl(const std::function<void()>& func,int timeLimitMs);

        template<typename Func>
        inline Core::ExecutionResult runIsolated(Func&& func, int timeLimitMs = DEFAULT_ISOLATION_TIMEOUT_MS) {
            return runIsolatedImpl(
                std::function<void()>(std::forward<Func>(func)),
                timeLimitMs
            );
        }

    #endif
    }
}

#endif
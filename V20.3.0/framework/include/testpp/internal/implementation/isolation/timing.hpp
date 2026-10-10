#pragma once

#ifndef TIMING_H
#define TIMING_H

#include "../../core.hpp"
#include "../../concepts.hpp"
#include "../../helpers.hpp"
#include "../isolation_types.hpp"

#ifdef _WIN32
    #include "../../runner.hpp"
#endif

namespace internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult timeout(Func&& func, int timeLimitMs) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func), timeLimitMs);
            #else
                Core::ExecutionResult result = isolateRun(func, timeLimitMs);
                return result;
            #endif
        }

        //Passes if it runs shorter than the passed in timeout
        template<typename Func> 
        inline Core::ExecutionResult completesWithin(Func&& func, int timeLimitMs) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func), timeLimitMs);
            #else
                Core::ExecutionResult result = isolateRun(func, timeLimitMs);
                return result;
            #endif
        }
    }
}

#endif
#pragma once

#ifndef FATAL_H
#define FATAL_H

#include "../../core/core.hpp"
#include "../../helpers.hpp"
#include "../isolation_types.hpp"

#ifdef _WIN32
    #include "../../runner.hpp"
#endif

#include <iostream>

namespace testpp::internal {
    namespace impl_iso {
        template<typename Func> 
        inline Core::ExecutionResult death(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult segfault(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        inline Core::ExecutionResult abort(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        Core::ExecutionResult fatal(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }

        template<typename Func> 
        Core::ExecutionResult nonFatal(Func&& func) {
            #ifdef _WIN32
                return runDeathTest(std::forward<Func>(func));
            #else
                Core::ExecutionResult result = isolateRun(func);
                return result;
            #endif
        }
    }
}

#endif
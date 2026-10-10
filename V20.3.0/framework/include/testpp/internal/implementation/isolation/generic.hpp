// #pragma once

// #ifndef GENERIC_H
// #define GENERIC_H

// #include "../../core/core.hpp"
// #include "../../helpers.hpp"
// #include "../isolation_types.hpp"

// #ifdef _WIN32
//     #include "../../runner.hpp"
// #endif

// namespace testpp::internal {
//     namespace impl_iso {
//         template<typename Func> 
//         inline Core::ExecutionResult executionStatus(Func&& func) {
//             #ifdef _WIN32
//                 return runDeathTest(std::forward<Func>(func));
//             #else
//                 Core::ExecutionResult result = isolateRun(func);
//                 return result;
//             #endif
//         }

//         template<typename Func> 
//         inline Core::ExecutionResult crashType(Func&& func) {
//             #ifdef _WIN32
//                 return runDeathTest(std::forward<Func>(func));
//             #else
//                 Core::ExecutionResult result = isolateRun(func);
//                 return result;
//             #endif
//         }

//         template<typename Func> 
//         inline Core::ExecutionResult terminationSignal(Func&& func) {
//             #ifdef _WIN32
//                 return runDeathTest(std::forward<Func>(func));
//             #else
//                 Core::ExecutionResult result = isolateRun(func);
//                 return result;
//             #endif
//         }

//         template<typename Func> 
//         inline Core::ExecutionResult processKilled(Func&& func) {
//             #ifdef _WIN32
//                 return runDeathTest(std::forward<Func>(func));
//             #else
//                 Core::ExecutionResult result = isolateRun(func);
//                 return result;
//             #endif
//         }
//     }
// }

// #endif
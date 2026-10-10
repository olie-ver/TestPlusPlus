// #pragma once

// #ifndef EXIT_H
// #define EXIT_H

// #include "../../core/core.hpp"
// #include "../../helpers.hpp"
// #include "../isolation_types.hpp"

// #ifdef _WIN32
//     #include "../../runner.hpp"
// #endif

// namespace testpp::internal {
//     namespace impl_iso {
//         template<typename Func> 
//         inline Core::ExecutionResult success(Func&& func) {
//             #ifdef _WIN32
//                 return runDeathTest(std::forward<Func>(func));
//             #else
//                 Core::ExecutionResult result = isolateRun(func);
//                 return result;
//             #endif
//         }

//         template<typename Func> 
//         inline Core::ExecutionResult failure(Func&& func) {
//             #ifdef _WIN32
//                 return runDeathTest(std::forward<Func>(func));
//             #else
//                 Core::ExecutionResult result = isolateRun(func);
//                 return result;
//             #endif
//         }

//         template<typename Func> 
//         inline Core::ExecutionResult nonzeroExit(Func&& func) {
//             #ifdef _WIN32
//                 return runDeathTest(std::forward<Func>(func));
//             #else
//                 Core::ExecutionResult result = isolateRun(func);
//                 return result;
//             #endif
//         }

//         template<typename Func> 
//         inline Core::ExecutionResult exitCode(Func&& func) {
//             #ifdef _WIN32
//                 return runDeathTest(std::forward<Func>(func));
//             #else
//                 Core::ExecutionResult result = isolateRun(func);
//                 return result;
//             #endif
//         }

//         template<typename Func> 
//         inline Core::ExecutionResult completes(Func&& func) {
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
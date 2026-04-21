#pragma once

#ifndef A_THROWS_H
#define A_THROWS_H

#include "../Core.hpp"
#include "../Runner.hpp"
#include "../Helpers.hpp"
#include <string>
#include <exception>

#define ASSERT_THROWS_1_ARGS(func) internal::Assert::assertThrows([&]() {(func);}, #func, __FILE__, __LINE__)
#define ASSERT_THROWS_2_ARGS(func, ex) internal::Assert::assertThrows<ex>([&]() {(func);}, #func, __FILE__, __LINE__)

#define GET_3RD_ARG(arg1, arg2, arg3, ...) arg3

#define ASSERT_THROWS_MACRO_CHOOSER(...) \
    GET_3RD_ARG(__VA_ARGS__, ASSERT_THROWS_2_ARGS, ASSERT_THROWS_1_ARGS)

//The actual tests
#define ASSERT_THROWS(...) ASSERT_THROWS_MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)
#define ASSERT_DOES_NOT_THROW(func) internal::Assert::assertDoesNotThrow([&](){(func);}, #func, __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief Checks if the passed in function throws an error, or a specified error
        /// @tparam Expected the expected thing that should be throw 
        /// @tparam Func the function type
        /// @param func the function
        /// @param funcName the name of the function
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <typename Expected = void, typename Func>
        inline void assertThrows(Func&& func, const char* funcName, const char* file, int line) {
            if constexpr (std::is_same_v<Expected, void>) {
                try {
                    func();
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Expected function \"") + funcName 
                        + std::string("\" to throw an exception, but it didn't"),
                        file,
                        line
                    });
                    throw Core::AssertionFailure();
                }
                catch (const std::exception& ex) {

                }  
                catch (...) {
                    
                }   
            } else {
                try {
                    func();
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Expected function \"") + funcName 
                        + std::string("\" to throw an exception, but it didn't"),
                        file,
                        line
                    });

                    throw Core::AssertionFailure();
                } catch (const Expected& ex) {

                } catch (...) {
                    std::string actualType = "unknown";
                    std::string expectedType = Helpers::demangle(typeid(Expected).name());

                    try {
                        throw;
                    } catch (const std::exception& ex) {
                        actualType = Helpers::demangle(typeid(ex).name());
                    } catch (...) {
                        actualType = "non-std::exception";
                    }

                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Expected function \"") + funcName +
                        "\" to throw exception of expected type: \"" 
                            + expectedType 
                            + "\" but got: \"" 
                            + actualType +'\"',
                        file,
                        line
                    });

                    throw Core::AssertionFailure();
                }
            }
        }

        /// @brief Checks that the passed in function doesn't throw anything
        /// @tparam Func the function's type
        /// @param func the passed in function
        /// @param funcName the name of the function
        /// @param file the file this function was called from
        /// @param line the line this function was called on
        template <typename Func>
        inline void assertDoesNotThrow(Func&& func, const char* funcName, const char* file, int line) {
            try {
                func();
            } catch (const std::exception& ex){
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected function \"") + funcName 
                    + std::string("\" to not throw an exception, but it did\n") 
                    + std::string("    Error message: \"") + ex.what() + "\"",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            } catch (...) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected function \"") + funcName 
                    + std::string("\" to not throw an exception, but it did\n") 
                    + std::string("    Exception type: unknown"),
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }
    }
}

#endif
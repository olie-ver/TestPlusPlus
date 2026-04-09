#pragma once

#ifndef E_THROWS_H
#define E_THROWS_H

#include "../Runner.hpp"
#include "../Helpers.hpp"
#include <string>

#include <exception>

#define EXPECT_THROWS(func) internal::Expect::throws([&]() {(func);}, #func, __FILE__, __LINE__)
#define EXPECT_THROWS_AS(func, ex) internal::Expect::throws<ex>([&]() {(func);}, #func, __FILE__, __LINE__)
#define EXPECT_DOES_NOT_THROW(func) internal::Expect::doesNotThrow([&](){(func);}, #func, __FILE__, __LINE__)

namespace internal {
    namespace Expect {
        template <typename Expected = void, typename Func>
        inline void throws(Func&& func, const char* funcName, const char* file, int line) {
            if constexpr (std::is_same_v<Expected, void>) {
                try {
                    func();
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Expected function \"") + funcName 
                        + std::string("\" to throw an exception, but it didn't"),
                        file,
                        line
                    });
                } catch (const std::exception& ex) {

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
                } catch (const Expected& ex) {

                } catch (const std::exception& ex) {
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
                }
            }
        }

        template <typename Func>
        inline void doesNotThrow(Func&& func, const char* funcName, const char* file, int line) {
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
            }
        }
    }
}

#endif
#pragma once

#ifndef META_H
#define META_H

#include "../Core.hpp"
#include "../Runner.hpp"
#include <functional>
#include <optional>
#include <string>

namespace internal {
    namespace impl_meta {
        inline std::optional<Core::Failure>
        passes(const std::function<void()>& test, const char* testName, 
            const char* file, const int line)
        {
            size_t oldSize = Runner::CURRENT_TEST->failures.size();

            //needs to take into account for things that throw => the assertion tests
            try {
                test();
            } catch(...) {

            }

            //if the number of failures grew
            if (oldSize < Runner::CURRENT_TEST->failures.size()) {
                //Get the last failure
                Core::Failure prev = Runner::CURRENT_TEST->failures.back();
                //Delete it
                Runner::CURRENT_TEST->failures.pop_back();
                //Return a new one
                return Core::Failure({
                    std::string("Expected test: ") + testName 
                    + " to pass, but it failed with message:\n"
                    + prev.message,
                    file,
                    line
                });
            }

            //in the case that the other test passes, this passes, so we can return
            return std::nullopt;
        }

        inline std::optional<Core::Failure>
        fails(const std::function<void()>& test, const char* testName, 
            const char* file, const int line)
        {
            size_t oldSize = Runner::CURRENT_TEST->failures.size();

            try {
                test();
            } catch(...) {

            }

            //if the number of failures didn't change
            if (Runner::CURRENT_TEST->failures.size() == oldSize) {
                std::string error = std::string("Expected test: ") + testName + " to fail, but it passed";
                //modify the old failure message to use this function's failure message
                return Core::Failure({
                    error,
                    file,
                    line
                });
            } else { //the test failed => this one passed => erase its error message
                Runner::CURRENT_TEST->failures.pop_back();
                return std::nullopt;
            }
        }

        inline std::optional<Core::Failure>
        failsWithMessage(const std::function<void()>& test, const char* testName, 
            const std::string msg, const char* file, const int line)
        {
            size_t oldSize = Runner::CURRENT_TEST->failures.size();

            try {
                test();
            } catch(...) {

            }

            //if the number of failures didn't change
            if (Runner::CURRENT_TEST->failures.size() == oldSize) {
                std::string error = std::string("Expected test: ") + testName + " to fail, but it passed";
                //modify the old failure message to use this function's failure message
                return Core::Failure({
                    error,
                    file,
                    line
                });
            } else { //The test failed
                Core::Failure last = Runner::CURRENT_TEST->failures.back();

                Runner::CURRENT_TEST->failures.pop_back(); //delete the old failure

                if (msg != last.message) { //failed with wrong message
                    return Core::Failure({
                        "Expected test to fail with message: \n\t\"" 
                        + msg
                        + "\"\n    but it failed with message: \n\t\""
                        + last.message + "\"",
                        file,
                        line
                    });
                }

                return std::nullopt; //failed with correct message
            }
        }
    }
}

#endif
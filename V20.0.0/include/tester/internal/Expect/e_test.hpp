#pragma once

#ifndef E_TEST_H
#define E_TEST_H

#include "../Runner.hpp"
#include <functional>

#define EXPECT_PASSES(test) internal::Expects::expectPasses([&](){(test);}, #test, __FILE__, __LINE__)
#define EXPECT_FAILS(test) internal::Expects::expectFails([&](){(test);}, #test, __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        inline void expectPasses(const std::function<void()>& test, const char* testName, 
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
                std::string error = std::string("Expected test: ") + testName 
                    + " to pass, but it failed with message:\n        "
                    + (Runner::CURRENT_TEST->failures.end() - 1)->message;

                //modify the old failure message to use this function's failure message
                *(Runner::CURRENT_TEST->failures.end() - 1) = {error, file, line};
            }
            //in the case that the other test passes, this passes, so we can return
        }

        inline void expectFails(const std::function<void()>& test, const char* testName, 
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
                Runner::CURRENT_TEST->failures.push_back({error, file, line});
            } else { //the test failed => this one passed => erase its error message
                Runner::CURRENT_TEST->failures.erase(Runner::CURRENT_TEST->failures.end() - 1);
            }
        }

        //Don't need this yet since we can't skip tests yet
        // inline void expectSkips() {

        // }
    }
}

#endif
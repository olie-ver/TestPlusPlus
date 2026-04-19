#pragma once

#ifndef E_STR_H
#define E_STR_H

#include "../Runner.hpp"
#include <string>
#include <initializer_list>

#define EXPECT_STR_EQ(first, second) internal::Expects::expectStringEquals((first), (second), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        //I need tests for string equals, string not equals, string empty, string not empty
        //need defined for std::string, char*, and char[]. Would be nice to also do the initializer 
        // list syntax as well
        // would be nice for initializer lists to be the first 
        //  or second parameter and have other types be the other parameter
        //  ie if there's an initializer list in one and an std::string in the other to handle that

        /// @brief An Expects test that checks if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringEquals(const std::string& first, const std::string& second, 
            const char* file, const int line) 
        {
            if (first != second) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a == b")
                    + "\n    a = \"" + first + '\"'
                    + "\n    b = \"" + second + '\"',
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test that checks if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringEquals(const char* first, const char* second, 
            const char* file, const int line) 
        {
            std::string error = "Null pointer passed in:";
            size_t initial_length = error.size();

            if (first == nullptr) {
                error += "\n     first = nullptr";
            }

            if (second == nullptr) {
                error += "\n     second = nullptr";
            }

            if (error.length() != initial_length) {
                Runner::CURRENT_TEST->failures.push_back({
                    error,
                    file,
                    line
                });
                return;
            }

            if (strcmp(first, second)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a == b")
                    + "\n    a = \"" + first + '\"'
                    + "\n    b = \"" + second + '\"',
                    file,
                    line
                });
            }
        }

        /// @brief An Expects test that checks if two strings are equal
        /// @tparam N the length of the first string
        /// @tparam M the length of the second string
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N, size_t M>
        inline void expectStringEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const int line) 
        {
            if (N != M) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Mismatched char[] lengths:")
                    + "\n    length of first = " + Helpers::toString(N)
                    + "\n    length of second = " + Helpers::toString(M),
                    file,
                    line
                });
                return;
            }

            for (size_t i = 0; i < N; i++) {
                if (first[i] != second[i]) {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Expected a == b")
                        + "\n    first = \"" + first + '\"'
                        + "\n    second = \"" + second + '\"',
                        file,
                        line
                    });
                    return;
                }
            }
        }

        //appears to be a fundamental issue with passing in an initializer list into a macro
        // inline void expectStringEquals(const std::initializer_list<char>& first, 
        //     const std::initializer_list<char>& second, 
        //     const char* file, 
        //     const int line) 
        // {
        //     std::string a = first;
        //     std::string b = second;
        //     expectStringEquals(a, b, file, line);
        // }
    }
}

#endif
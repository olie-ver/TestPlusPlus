#pragma once

#ifndef E_STR_H
#define E_STR_H

#include "../Runner.hpp"
#include <string>
#include <iostream>

#define EXPECT_STR_EQ(a, b) internal::Expect::stringEqual((a), (b), __FILE__, __LINE__)
#define EXPECT_STR_NE(a, b) internal::Expect::stringNotEqual((a), (b), __FILE__, __LINE__)

namespace internal {
    namespace Expect {
        /// @brief Checks if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void stringEqual(const std::string& first, const std::string& second, const char* file, int line) {
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

        /// @brief Checks if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void stringEqual(const char* first, const char* second, const char* file, int line) {
            std::string message = "Null pointer passed in:";
            size_t initialLength = message.length();

            if (first == nullptr) {
                message += "\n     a = nullptr";
            }
            if (second == nullptr) {
                message += "\n     b = nullptr";
            }

            if (message.length() != initialLength) {
                Runner::CURRENT_TEST->failures.push_back({
                    message,
                    file,
                    line
                });
                return;
            }

            stringEqual(std::string(first), std::string(second), file, line);
        }

        /// @brief Checks if two strings are not equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void stringNotEqual(const std::string& first, const std::string& second, const char* file, int line) {
            if (first == second) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a != b")
                    + "\n    a = \"" + first + '\"'
                    + "\n    b = \"" + second + '\"',
                    file,
                    line
                });
            }
        }

        /// @brief Checks if two strings are not equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void stringNotEqual(const char* first, const char* second, const char* file, int line) {
            std::string message = "Null pointer passed in:";
            size_t initialLength = message.length();

            if (first == nullptr) {
                message += "\n     a = nullptr";
            }
            if (second == nullptr) {
                message += "\n     b = nullptr";
            }

            if (message.length() != initialLength) {
                Runner::CURRENT_TEST->failures.push_back({
                    message,
                    file,
                    line
                });
                return;
            }

            stringNotEqual(std::string(first), std::string(second), file, line);
        }
    }
}

#endif
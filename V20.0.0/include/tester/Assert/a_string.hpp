#pragma once

#ifndef A_STR_H
#define A_STR_H

#include "../Core.hpp"
#include "../Runner.hpp"
#include "../Helpers.hpp"
#include <algorithm>
#include <string>

#define EXPECT_STR_EQ(first, second) internal::Assert::assertStringEquals((first), (second), __FILE__, __LINE__)
#define EXPECT_STR_NE(first, second) internal::Assert::assertStringNotEquals((first), (second), __FILE__, __LINE__)
#define EXPECT_STR_EMT(first) internal::Assert::assertStringEmpty((first), __FILE__, __LINE__)
#define EXPECT_STR_NEMT(first) internal::Assert::assertStringNotEmpty((first), __FILE__, __LINE__)

namespace internal {
    namespace Assert {
        /// @brief An Assert test that asserts if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringEquals(const std::string& first, const std::string& second, 
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

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that asserts if two strings are equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringEquals(const char* first, const char* second, 
            const char* file, const int line) 
        {
            std::string error = "Null pointer passed in:";
            size_t initial_length = error.size();

            bool first_null = false;
            bool second_null = false;

            if (first == nullptr) {
                error += "\n     first = nullptr";
                first_null = true;
            }

            if (second == nullptr) {
                error += "\n     second = nullptr";
                second_null = true;
            }

            if (first_null && second_null) {
                return;
            }

            if (error.length() != initial_length) {
                Runner::CURRENT_TEST->failures.push_back({
                    error,
                    file,
                    line
                });
                throw Core::AssertionFailure();
            }

            if (strcmp(first, second)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a == b")
                    + "\n    a = \"" + first + '\"'
                    + "\n    b = \"" + second + '\"',
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that asserts if two strings are equal
        /// @tparam N the length of the first string
        /// @tparam M the length of the second string
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N, size_t M>
        inline void assertStringEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const int line) 
        {
            //create displayable copies of the parameters
            char a[N + 1];
            char b[M + 1];
            std::copy(std::begin(first), std::end(first), std::begin(a));
            std::copy(std::begin(second), std::end(second), std::begin(b));
            a[N] = '\0';
            b[M] = '\0';

            size_t low_bound = std::min(N, M);
            size_t up_bound = std::max(N, M);

            for (size_t i = 0; i < low_bound; i++) {
                if (first[i] != second[i]) { //both not equal
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Expected a == b")
                        + "\n    first = \"" + a + '\"'
                        + "\n    second = \"" + b + '\"',
                        file,
                        line
                    });
                    
                    throw Core::AssertionFailure();
                } else { //both are equal
                    if (first[i] == '\0') { //both have terminated
                        return;
                    }
                }
            }

            //Both were equal up to the smaller of N and M and neither terminated
            if (N != M) {
                //if the larger char[] doesn't terminate after this point, their lengths are considered
                //  mismatched.
                if (up_bound == N && first[low_bound] != '\0') { //the first string is the larger one
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Mismatched char[] lengths:")
                        + "\n    length of first = " + Helpers::toString(N)
                        + "\n    length of second = " + Helpers::toString(M),
                        file,
                        line
                    });

                    throw Core::AssertionFailure();
                } else if (up_bound == M && second[low_bound] != '\0') {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Mismatched char[] lengths:")
                        + "\n    length of first = " + Helpers::toString(N)
                        + "\n    length of second = " + Helpers::toString(M),
                        file,
                        line
                    });

                    throw Core::AssertionFailure();
                }
            }
        }

        /// @brief An Assert test that asserts if two strings are not equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringNotEquals(const std::string& first, 
            const std::string& second, 
            const char* file, 
            const int line) 
        {
            if (first == second) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a == b")
                    + "\n    a = \"" + first + '\"'
                    + "\n    b = \"" + second + '\"',
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that asserts if two strings are not equal
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringNotEquals(
            const char* first, 
            const char* second, 
            const char* file,
            const int line) 
        {
            bool first_null = (first == nullptr);
            bool second_null = (second == nullptr);

            if (first_null ^ second_null) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Mismatched nullptrs")
                    + "\n    a = nullptr: " + Helpers::toString(first_null)
                    + "\n    b = nullptr:" + Helpers::toString(second_null),
                    file,
                    line
                });
                
                throw Core::AssertionFailure();
            }

            if (!strcmp(first, second)) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a != b")
                    + "\n    a = \"" + first + '\"'
                    + "\n    b = \"" + second + '\"',
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that asserts if two strings are not equal
        /// @tparam N the length of the first string
        /// @tparam M the length of the second string
        /// @param first the first string
        /// @param second the second string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N, size_t M>
        inline void expectStringNotEquals(const char(&first)[N], const char(&second)[M], 
            const char* file, const int line) 
        {
            //create displayable copies of the parameters
            char a[N + 1];
            char b[M + 1];
            std::copy(std::begin(first), std::end(first), std::begin(a));
            std::copy(std::begin(second), std::end(second), std::begin(b));
            a[N] = '\0';
            b[M] = '\0';

            size_t low_bound = std::min(N, M);

            for (size_t i = 0; i < low_bound; i++) {
                if (first[i] != second[i]) {
                    return;
                }
            }

            //they were equal up to low_bound, and if N == M, low_bound == up_bound, hence they're equal
            if (N == M) {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a != b")
                    + "\n    first = \"" + a + '\"'
                    + "\n    second = \"" + b + '\"',
                    file,
                    line
                });
                throw Core::AssertionFailure();
            }

            //the lengths aren't equal, but they've still been equal, so now need to check if the larger one
            //  terminates or not
            //if the larger one terminates => they are equal, otherwise, they are not equal

            if (low_bound == N && second[low_bound] == '\0') {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a != b")
                    + "\n    first = \"" + a + '\"'
                    + "\n    second = \"" + b + '\"',
                    file,
                    line
                });

                throw Core::AssertionFailure();
            } else if (low_bound == M && first[low_bound] == '\0') {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected a != b")
                    + "\n    first = \"" + a + '\"'
                    + "\n    second = \"" + b + '\"',
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that tests if a string is empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringEmpty(std::string& first, const char* file, const int line) {
            if (!first.empty()) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected string to be empty, but wasn't: first = " + first,
                    file,
                    line
                }); 

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that tests if a string is empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void assertStringEmpty(const char* first, const char* file, const int line) {
            if (first == nullptr) {
                Runner::CURRENT_TEST->failures.push_back({
                    "nullptr passed in",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }

            if (first[0] != '\0') {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected string to be empty, but wasn't: first = ") + first,
                    file,
                    line
                }); 

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that tests if a string is empty
        /// @tparam N the size of the array
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N>
        inline void assertStringEmpty(const char(&first)[N], const char* file, const int line) {
            char a[N + 1];
            std::copy(std::begin(first), std::end(first), std::begin(a));
            a[N] = '\0';
            if (first[0] != '\0') {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected string to be empty, but wasn't: first = ") + a,
                    file,
                    line
                }); 
                
                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that tests if a string is not empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringNotEmpty(std::string& first, const char* file, const int line) {
            if (first.empty()) {
                Runner::CURRENT_TEST->failures.push_back({
                    "Expected string to not be empty, but was",
                    file,
                    line
                }); 

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that tests if a string is not empty
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        inline void expectStringNotEmpty(const char* first, const char* file, const int line) {
            if (first == nullptr) {
                Runner::CURRENT_TEST->failures.push_back({
                    "nullptr passed in",
                    file,
                    line
                });

                throw Core::AssertionFailure();
            }

            if (first[0] == '\0') {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected string to not be empty, but was"),
                    file,
                    line
                }); 

                throw Core::AssertionFailure();
            }
        }

        /// @brief An Assert test that tests if a string is not empty
        /// @tparam N the size of the array
        /// @param first the string
        /// @param file the file the function was called from
        /// @param line the line the function was called on
        template <size_t N>
        inline void assertStringNotEmpty(const char(&first)[N], const char* file, const int line) {
            if (first[0] == '\0') {
                Runner::CURRENT_TEST->failures.push_back({
                    std::string("Expected string to not be empty, but was"),
                    file,
                    line
                }); 

                throw Core::AssertionFailure();
            }
        }
    }
}

#endif
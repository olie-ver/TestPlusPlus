#pragma once

#ifndef E_SET_H
#define E_SET_H

#include "../Concepts.hpp"
#include "../Helpers.hpp"
#include "../Runner.hpp"
#include <ranges>
#include <string>

#define EXPECT_SET_EQ(first, second) internal::Expects::expectSameSet((first), (second), __FILE__, __LINE__)
#define EXPECT_SET_NE(first, second) internal::Expects::expectNotSameSet((first), (second), __FILE__, __LINE__)
#define EXPECT_SUBSET(first, second) internal::Expects::expectSubset((first), (second), __FILE__, __LINE__)
#define EXPECT_SUPERSET(first, second) internal::Expects::expectSuperset((first), (second), __FILE__, __LINE__)
#define EXPECT_STRICT_SUBSET(first, second) internal::Expects::expectStrictSubset((first), (second), __FILE__, __LINE__)

namespace internal {
    namespace Expects {
        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectSameSet(const A& a, const B& b, const char* file, const int line) {
            //everything in A appears in B, and everything in B appears in A
            auto a_itr = std::ranges::cbegin(a);
            auto a_end = std::ranges::cend(a);
            auto b_end = std::ranges::cend(b);

            //check that everything in A appears in B
            for (; a_itr != a_end; ++a_itr) {
                auto b_itr = std::ranges::cbegin(b);

                bool found = false;
                for (; b_itr != b_end; ++b_itr) {
                    if (*a_itr == *b_itr) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Element in first not present in second: " 
                            + Helpers::toString(*a_itr)),
                        file,
                        line
                    });
                    return;
                }
            }

            //check that everything in B appears in A
            auto b_itr = std::ranges::cbegin(b); //get the start of B since we're checking B now
            for (; b_itr != b_end; ++b_itr) {
                a_itr = std::ranges::cbegin(a); //RESET a_itr to point at the beginning again
                bool found = false;
                for (; a_itr != a_end; ++a_itr) {
                    if (*a_itr == *b_itr) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                     Runner::CURRENT_TEST->failures.push_back({
                        std::string("Element in second not present in first: " 
                            + Helpers::toString(*b_itr)),
                        file,
                        line
                    });
                    return;
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectNotSameSet(const A& a, const B& b, const char* file, const int line) {
            //not everything in A appears in B, or not everything in B appears in A

            auto a_itr = std::ranges::cbegin(a);
            auto a_end = std::ranges::cend(a);
            auto b_end = std::ranges::cend(b);

            for (; a_itr != a_end; ++a_itr) {
                auto b_itr = std::ranges::cbegin(b);
                bool found = false;

                for (; b_itr != b_end; ++b_itr) {
                    if (*a_itr == *b_itr) {
                        found = true;
                        break;
                    }
                }

                //something in A is not in B => not the same set => return
                if (!found) {
                    return;
                }
            }

            auto b_itr = std::ranges::cbegin(b);

            for (; b_itr != b_end; ++b_itr) {
                a_itr = std::ranges::cbegin(a);
                bool found = false;

                for (; a_itr != a_end; ++a_itr) {
                    if (*a_itr == *b_itr) {
                        found = true;
                        break;
                    }
                }

                //something in B is not in A => not the same set => return
                if (!found) {
                    return;
                }
            }

            Runner::CURRENT_TEST->failures.push_back({
                "Both sets are the same",
                file,
                line
            });
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectSubset(const A& sub, const B& super, const char* file, const int line) {
            //everything in sub appears in super
            auto a_itr = std::ranges::cbegin(sub);

            auto a_end = std::ranges::cend(sub);
            auto b_end = std::ranges::cend(super);

            for (; a_itr != a_end; ++a_itr) {
                auto b_itr = std::ranges::cbegin(super);
                bool found = false;
                for (; b_itr != b_end; ++b_itr) {
                    if (*a_itr == *b_itr) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Element in first not present in second: " 
                            + Helpers::toString(*a_itr)),
                        file,
                        line
                    });
                    return;
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectSuperset(const A& super, const B& sub, const char* file, const int line) {
            //everything in B appears in A
            auto b_itr = std::ranges::cbegin(sub);

            auto a_end = std::ranges::cend(super);
            auto b_end = std::ranges::cend(sub);

            for (; b_itr != b_end; ++b_itr) {
                auto a_itr = std::ranges::cbegin(super);
                bool found = false;
                for (; a_itr != a_end; ++a_itr) {
                    if (*a_itr == *b_itr) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    Runner::CURRENT_TEST->failures.push_back({
                        std::string("Element in second not present in first: " 
                            + Helpers::toString(*b_itr)),
                        file,
                        line
                    });
                    return;
                }
            }
        }

        template <typename A, typename B>
        requires Concepts::IterableAndComparable<A, B>
        inline void expectStrictSubset(const A& sub, const B& super, const char* file, const int line) {
            //everything in A appears in B, but B has at least one element that does not appear in A

            //create a new scope for easier reasoning on variables
            {
                auto a_itr = std::ranges::cbegin(sub);

                auto a_end = std::ranges::cend(sub);
                auto b_end = std::ranges::cend(super);

                for (; a_itr != a_end; ++a_itr) {
                    auto b_itr = std::ranges::cbegin(super);
                    bool found = false;
                    for (; b_itr != b_end; ++b_itr) {
                        if (*a_itr == *b_itr) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        Runner::CURRENT_TEST->failures.push_back({
                            std::string("Element in first not present in second: " 
                                + Helpers::toString(*a_itr)),
                            file,
                            line
                        });
                        return;
                    }
                }
            }

            //after this point, everything in A has been found in B
            //now need to check if there's something in B that's not in A

            //create new scope for easier reasoning on variables
            {
                auto b_itr = std::ranges::cbegin(super);
                auto b_end = std::ranges::cend(super);
                auto a_end = std::ranges::cend(sub);

                for (; b_itr != b_end; ++b_itr) {
                    auto a_itr = std::ranges::cbegin(sub);

                    bool found = false;
                    for (; a_itr != a_end; ++a_itr) {
                        if (*b_itr == *a_itr) {
                            found = true; 
                            break;
                        }
                    }

                    //if there's an element in B that's not in A, 
                    //  A is a strict subset => return
                    if (!found) {
                        return;
                    }
                }

                Runner::CURRENT_TEST->failures.push_back({
                    "First is not a strict subset of Second (everything in Second is in First)" ,
                    file,
                    line
                });
                return;
            }
        }
    }
}

#endif
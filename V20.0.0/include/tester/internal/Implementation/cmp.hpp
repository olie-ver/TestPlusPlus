#pragma once

#ifndef CMP_H
#define CMP_H

#include "../Core.hpp"
#include "../Concepts.hpp"
#include "../Helpers.hpp"
#include <optional>
#include <string>

namespace internal {
    namespace impl_cmp {
        template <typename A, typename B>
        requires Concepts::HasEQ<A, B>
        inline std::optional<const Core::Failure> equals(const A& a, const B& b, const char* file, const int line) {
            if (!(a == b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);
                return Core::Failure(
                    "Expected: a == b \n\ta = " + aStr + "\n\tb = " + bStr,
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <typename A, typename B>
        requires (Concepts::HasNE<A, B> || Concepts::HasEQ<A, B>)
        inline std::optional<const Core::Failure>
        notEquals(const A& a, const B& b, const char* file, const int line) {
            if constexpr(Concepts::HasNE<A, B>) {
                if (!(a != b)) {
                    std::string aStr = Helpers::toString(a);
                    std::string bStr = Helpers::toString(b);

                    return Core::Failure(
                        "Expected: a != b \n\ta = " + aStr + "\n\tb = " + bStr,
                        file,
                        line
                    );
                }

                return std::nullopt;
            } else {
                if (a == b) {
                    std::string aStr = Helpers::toString(a);
                    std::string bStr = Helpers::toString(b);

                    return Core::Failure(
                        "Expected: a != b \n\ta = " + aStr + "\n\tb = " + bStr,
                        file,
                        line
                    );
                }

                return std::nullopt;
            }
        }

        template <typename A, typename B>
        requires(Concepts::HasLT<A, B>)
        inline std::optional<const Core::Failure> 
        lessThan(const A& a, const B& b, const char* file, const int line) {
            if (!(a < b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);

                return Core::Failure(
                    "Expected: a < b \n\ta = " + aStr + "\n\tb = " + bStr,
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <typename A, typename B>
        requires(Concepts::HasLE<A, B>)
        inline std::optional<const Core::Failure> 
        lessThanEqual(const A& a, const B& b, const char* file, const int line) {
            if (!(a <= b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);

                return Core::Failure(
                    "Expected: a <= b \n\ta = " + aStr + "\n\tb = " + bStr,
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <typename A, typename B>
        requires(Concepts::HasGT<A, B>)
        inline std::optional<const Core::Failure> 
        greaterThan(const A& a, const B& b, const char* file, const int line) {
            if (!(a > b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);

                return Core::Failure(
                    "Expected: a > b \n\ta = " + aStr + "\n\tb = " + bStr,
                    file,
                    line
                );
            }

            return std::nullopt;
        }

        template <typename A, typename B>
        requires(Concepts::HasGE<A, B>)
        inline std::optional<const Core::Failure> 
        greaterThanEqual(const A& a, const B& b, const char* file, const int line) {
            if (!(a >= b)) {
                std::string aStr = Helpers::toString(a);
                std::string bStr = Helpers::toString(b);

                return Core::Failure(
                    "Expected: a >= b \n\ta = " + aStr + "\n\tb = " + bStr,
                    file,
                    line
                );
            }
        }
    }
}

#endif
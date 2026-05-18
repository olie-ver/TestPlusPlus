#pragma once

#ifndef FLT_EQ_H
#define FLT_EQ_H

#include "../flt.hpp"

namespace internal {
    namespace impl_flt {
        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1>
        inline std::optional<const Core::Failure> 
            absolutelyEqual(A a, B b, T1 abs_tol, const char* file, int line) 
        {
            using T = std::common_type_t<A, B, T1>;
            
            T aa = static_cast<T>(a);
            T bb = static_cast<T>(b);
            T absTol = static_cast<T>(abs_tol);

            if (std::abs(aa - bb) > std::abs(absTol)) {
                return Core::Failure({
                    std::string("Expected |a - b| <= |abs_tol|") 
                        + "\n      a = " + Helpers::toString(aa) 
                        + "\n      b = " + Helpers::toString(bb) 
                        + "\n      abs_tol = " + Helpers::toString(absTol),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename A, typename B, typename T1, typename T2>
        requires Concepts::CommonFloat<A, B, T1, T2>
        inline std::optional<const Core::Failure> 
            nearlyEqual(A a, B b, T1 abs_tol, T2 rel_tol, const char* file, int line) 
        {
            using T = std::common_type_t<A, B, T1, T2>;

            T aa = static_cast<T>(a);
            T bb = static_cast<T>(b);
            T absTol = static_cast<T>(abs_tol);
            T relTol = static_cast<T>(rel_tol);

            if (std::abs(aa - bb) > std::max(std::abs(absTol), 
                    std::abs(relTol) * std::max(std::abs(aa), std::abs(bb)))) 
            {
                return Core::Failure({
                    std::string("Expected |a - b| <= max(abs_tol, rel_tol * max(|a|, |b|))") 
                        + "\n      a = " + Helpers::toString(aa) 
                        + "\n      b = " + Helpers::toString(bb) 
                        + "\n      abs_tol = " + Helpers::toString(absTol)
                        + "\n      rel_tol = " + Helpers::toString(relTol),
                    file,
                    line
                });
            }

            return std::nullopt;
        }

        template <typename A, typename B, typename T1>
        requires Concepts::CommonFloat<A, B, T1, T1>
        std::optional<const Core::Failure>
            relativelyEqual(A a, B b, T1 rel_tol, const char* file, int line) 
        {
            using T = std::common_type_t<A, B, T1>;

            T aa = static_cast<T>(a);
            T bb = static_cast<T>(b);
            T relTol = static_cast<T>(rel_tol);

            if (std::abs(aa - bb) > std::abs(relTol) * std::max(std::abs(aa), std::abs(bb))) {
                return Core::Failure({
                    std::string("Expected |a - b| <= rel_tol * max(|a|, |b|)") 
                        + "\n      a = " + Helpers::toString(aa) 
                        + "\n      b = " + Helpers::toString(bb) 
                        + "\n      rel_tol = " + Helpers::toString(relTol),
                    file,
                    line
                });
            }

            return std::nullopt;
        }
    }
}

#endif
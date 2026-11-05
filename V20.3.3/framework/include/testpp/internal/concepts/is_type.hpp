#pragma once

#ifndef TESTPP_CONCEPTS_IS_TYPE_H
#define TESTPP_CONCEPTS_IS_TYPE_H

#include <concepts>

namespace testpp::internal {
    namespace Concepts {
        //A concept for a common floating point type
        template <typename A, typename B, typename C, typename D>
        concept CommonFloat = requires() {
            std::is_floating_point<std::common_type<A, B, C, D>>::value;
        };
    }
}

#endif
#pragma once

#ifndef EXPECT_H
#define EXPECT_H

#include "Expect/e_bool.hpp"
#include "Expect/e_cmp.hpp"
#include "Expect/e_flt.hpp"
#include "Expect/e_null.hpp"
#include "Expect/e_string.hpp"
#include "Expect/e_throws.hpp"
// #include "Expect/e_iterable.hpp"

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief A tests namespace containing different tests for expecting
    namespace Expects {
    }
}

#endif
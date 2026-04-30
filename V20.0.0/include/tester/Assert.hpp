#pragma once

#ifndef ASSERT_H
#define ASSERT_H

#include <exception>

#include "Assert/a_bool.hpp"
#include "Assert/a_cmp.hpp"
#include "Assert/a_flt.hpp"
#include "Assert/a_itr.hpp"
#include "Assert/a_null.hpp"
#include "Assert/a_throws.hpp"

/// @brief An internal namespace. Using anything from within is not advised
namespace internal {
    /// @brief A tests namespace containing different tests for asserting
    namespace Assert {
    }
}

#endif
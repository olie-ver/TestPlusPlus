#pragma once

#ifndef TESTPP_RESET_COMMANDS_H
#define TESTPP_RESET_COMMANDS_H

#include <array>
#include <string_view>

namespace testppCLI {
    /// @brief Resets the argument flags, compiler flags, and linked library flags to the global settings
    void reset();

    /// @brief Resets just the argument flags to the global settings
    void resetFlags();

    /// @brief Resets the compiler flags to the global settings
    void resetCxx();

    /// @brief Resets the linked library flags to the global settings
    void resetLink();

    /// @brief Resets all argument flags, compiler flags, and linked library flags to the global settings GLOBALLY
    void globalReset();

    /// @brief Resets all argument flags to the global settings GLOBALLY
    void globalResetFlags();

    /// @brief Resets all compiler flags to the global settings GLOBALLY
    void globalResetCxx();

    /// @brief Resets all linked library flags to the global settings GLOBALLY
    void globalResetLink();

    /// @brief Resets all argument flags, compiler flags, and linked library flags to the DEFAULT settings
    void defaultReset();

    /// @brief Resets all argument flags to the DEFAULT settings
    void defaultFlags();

    /// @brief Resets all compiler flags to the DEFAULT settings
    void defaultCxx();

    /// @brief Resets all linked library flags to the DEFAULT settings
    void defaultLink();

    /// @brief Resets all argument flags, compiler flags, and linked library flags to the DEFAULT settings GLOBALLY
    void globalDefaultReset();

    /// @brief Resets all argument flags to the DEFAULT settings GLOBALLY
    void globalDefaultFlags();

    /// @brief Resets all compiler flags to the DEFAULT settings GLOBALLY
    void globalDefaultCxx();

    /// @brief Resets all linked library flags to the DEFAULT settings GLOBALLY
    void globalDefaultLink();
}

#endif
#pragma once

#ifndef TESTPP_FILE_SYSTEM_H
#define TESTPP_FILE_SYSTEM_H

#include "Metadata.hpp"

#include <array>
#include <filesystem>
#include <string_view>

namespace testppCLI {
    constinit static std::array<std::string_view, 53> commands{
        "--v=", "--verbosity=", 
        "--t=", "--threads=", "--numthreads=", 
        "--timeout=", "--timeout_sec=", "--timeout_ms=",
        "--s=", "--skip=",
        "--testonly=", "--test_only=", "--to=", "--t_o=",
        "--json", "--junit", "--xml", 
        "--stdoutsize=", "--stdout=", "--stderrsize=", "--stderr=",
        "--truncate",
        "--stream",
        "--help", "--h",
        "--diagnostics", "--d",
        "--version", "--v",
        "--list", "--l",
        "--reset", "--reset-flags", "--reset-cxx", "--reset-link",
        "--default", "--default-flags", "--default-cxx", "--default-link",
        "--g", "--global",
        "--config", "--cxx", "--link", 
        "--default", "--default-flags", "--default-cxx", "--default-link",
        "--set-exec", "--set",
        "--new", "--inspect", "--rename"
    };

    /// @brief Gets the path to the root folder of where Test++ is installed
    /// @return The path of the root folder where Test++ is installed
    std::filesystem::path GetInstallRoot();

    /// @brief Gets the name of the last ran executable 
    /// @return The path to the last executable's folder
    std::filesystem::path GetLastExec();

    /// @brief Deletes an executable folder if it exists
    /// @param name The name of the executable that should be deleted
    void deleteExec(int argc, char** argv);

    /// @brief Checks if the name belongs to an executable directory
    /// @param name The name of the executable directory that should be checked for
    /// @return true if the name belongs to an executable directory, false otherwise
    bool IsExec(std::string_view name);

    bool IsFlag(std::string_view name);

    /// @brief Gets the Metadata associated with the associated name
    /// @param name the name of the executable
    /// @return the Metadata of the executable
    Metadata GetMetadata(std::string_view name);
}

#endif
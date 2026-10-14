#pragma once

#ifndef TESTPP_CONFIG_H
#define TESTPP_CONFIG_H

#include <filesystem>
#include <ostream>
#include <string>

namespace testppCLI {
    /// @brief A struct containing all the information about how the user wants to configure the 
    /// usage of the Test++ framework
    struct Config {
        /// @brief Allows the user to pass Config to std::cout <<
        friend std::ostream& operator<< (std::ostream& stream, const Config& config);

        /// @brief Serializes a Config to the specified filepath
        /// @param path the path where the Config should go to
        void Serialize(const std::filesystem::path& path);

        /// @brief Deserializes a Config from the specified filepath
        /// @param path the path where the Config should come from
        /// @return The Config containing all data and methods of what was serialized
        static Config Deserialize(const std::filesystem::path& path);

        enum TimeUnit {
            sec,
            ms
        };

        uint64_t num_threads = 1;
        uint64_t timeout = 0;
        uint64_t stdoutSize = 0;
        uint64_t stderrSize = 0;
        uint8_t stream = false;
        TimeUnit timeUnit = sec;

        std::string jsonFile;
        std::string jUnitFile;

        std::string verbosity = "default";

        std::string skipSuites;
        std::string testOnlySuites;
    };

    /// @brief A struct containing the user's compiler preferences including language standard,
    /// compiler flags, and libraries to link with 
    struct CXX {
        /// @brief Allows the user to pass CXX to std::cout <<
        friend std::ostream& operator<< (std::ostream& stream, const CXX& cxx);

        /// @brief Serializes a CXX to the specified filepath
        /// @param path the path where the CXX should go to
        void Serialize(const std::filesystem::path& path);

        /// @brief Deserializes a CXX from the specified filepath
        /// @param path the path where the CXX should come from
        /// @return The CXX containing all data and methods of what was serialized
        static CXX Deserialize(const std::filesystem::path& path);

        uint8_t standard = 20;
        std::string flags;
        std::string linkLibs;
        std::string include;
    };

    /// @brief Sets the user's default executable to the executable at argv[2]
    /// @param argc the number of CLI args
    /// @param argv the CLI args
    void setExec(int argc, char** argv);

    /// @brief Creates a new test executable using the parameter argv[2]
    /// @param argc the number of CLI args
    /// @param argv the CLI args
    void createExec(int argc, char** argv);

    /// @brief Configures the flags of the current executable
    /// @param argc the number of CLI args
    /// @param argv the CLI args
    void configureFlags(int argc, char** argv);

    /// @brief Configures the compiler flags of the current executable
    /// @param argc the number of CLI args
    /// @param argv the CLI args
    void configureCXX(int argc, char** argv);

    /// @brief Configures the libraries the current executable will be linked against
    /// @param argc the number of CLI args
    /// @param argv the CLI args
    void configureLink(int argc, char** argv);

    /// @brief Configures the include paths the current executable will have
    /// @param argc the number of CLI args
    /// @param argv the CLI args
    void configureInclude(int argc, char** argv);

    /// @brief Globally configures the flags of all executables
    /// @param begin the index to start parsing argv
    /// @param end the index to stop parsing argv
    /// @param argv the CLI args
    void globalConfigureFlags(int begin, int end, char** argv);

    /// @brief Globally configures the compiler flags of all executables
    /// @param begin the index to start parsing argv
    /// @param end the index to stop parsing argv
    /// @param argv the CLI args
    void globalConfigureCXX(int begin, int end, char** argv);

    /// @brief Globally configures the libraries the current executable will be linked against
    /// @param begin the index to start parsing argv
    /// @param end the index to stop parsing argv
    /// @param argv the CLI args
    void globalConfigureLink(int begin, int end, char** argv);

    /// @brief Globally configures the include paths of the current executable
    /// @param begin the index to start parsing argv
    /// @param end the index to stop parsing argv
    /// @param argv the CLI args
    void globalConfigureInclude(int begin, int end, char** argv);
}

#endif
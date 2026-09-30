#pragma once

#ifndef TESTPP_METADATA_H
#define TESTPP_METADATA_H

#include "Configure.hpp"

namespace testppCLI {
    struct Metadata {
        /// @brief Allows the user to pass Config to std::cout <<
        friend std::ostream& operator<< (std::ostream& stream, const Metadata& meta);

        /// @brief Serializes a Config to the specified filepath
        /// @param path the path where the Config should go to
        void Serialize(const std::filesystem::path& path);

        /// @brief Deserializes a Config from the specified filepath
        /// @param path the path where the Config should come from
        /// @return The Config containing all data and methods of what was serialized
        static Metadata Deserialize(const std::filesystem::path& path);

        bool compile = true;
        std::string files = "";
    };
}

#endif
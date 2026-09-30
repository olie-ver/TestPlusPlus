#include "../../headers/Helpers.hpp"

#include "../../headers/FileSystem.hpp"

#include <iostream>
#include <sstream>

namespace testppCLI {
    void buildExec(std::string_view name) {
        std::filesystem::path execDir{GetInstallRoot() / "run" / "testpp" / name};

        std::stringstream stream{"cmake -S \""};
        stream << execDir << "\" -B \"" << execDir << '\"';

        int configResult = std::system(stream.str().c_str());

        if (configResult != 0) {
            std::cerr << "Failed to configure test executable: " << stream.str() << '\n';
            abort();
        }

        stream.clear();
        #if defined(_WIN32) || defined(_WIN64) 
            stream << "--build \"" << execDir << "\" --config Release";
        #else
            stream << "--build \"" << execDir << '\"';
        #endif

        int buildResult = std::system(stream.str().c_str());

        if (buildResult != 0) {
            std::cerr << "Failed to build test executable: " << stream.str() << '\n';
        }
    }
}
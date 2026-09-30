#include "../../headers/Helpers.hpp"

#include "../../headers/FileSystem.hpp"

#include <iostream>
#include <sstream>

namespace testppCLI {
    void buildExec(std::string_view name) {
        std::filesystem::path execDir{GetInstallRoot() / "run" / "testpp" / name};

        std::stringstream stream;
        stream << "cmake -S \"" << execDir << "\" -B \"" << execDir << '"';

        int configResult = std::system(stream.str().c_str());

        if (configResult != 0) {
            std::cerr << "Failed to configure test executable: " << stream.str() << '\n';
            abort();
        }

        stream.str(std::string());
        #if defined(_WIN32) || defined(_WIN64) 
            stream << "cmake --build \"" << execDir << "\" --config Release";
        #else
            stream << "cmake --build \"" << execDir << '\"';
        #endif

        int buildResult = std::system(stream.str().c_str());

        std::cout << "Build test executable at: " << stream.str() << '\n';

        if (buildResult != 0) {
            std::cerr << "Failed to build test executable: " << stream.str() << '\n';
        }
    }
}
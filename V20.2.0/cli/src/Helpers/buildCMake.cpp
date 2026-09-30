#include "../../headers/Helpers.hpp"

#include "../../headers/FileSystem.hpp"

#include <fstream>
#include <sstream>

#include <iostream>

namespace testppCLI {
    void buildCMake(std::string_view name) {
        Metadata metadata = GetMetadata(name);

        std::filesystem::path execDir{GetInstallRoot() / "run" / "testpp" / name};
        std::filesystem::path defaultCmake{GetInstallRoot() / "var" / "CMakeLists.txt.in"};

        std::ifstream ifstream{defaultCmake};
        std::stringstream cmake;
        cmake << ifstream.rdbuf();

        std::string filecontents{cmake.str()};

        CXX cxx = CXX::Deserialize(execDir / "cxx.conf");

        const std::string& srcFiles = replace(metadata.files, " ", "\n\t");
        const std::string& flags = replace(cxx.flags, " ", "\n\t");
        const std::string& libs = replace(cxx.linkLibs, " ", "\n\t");

        const std::string installReplace = "@INSTALL_PREFIX@";
        const std::string srcReplace = "@USER_SOURCES@";
        const std::string stdReplace = "@CXX_STANDARD@";
        const std::string flagReplace = "@USER_CXX_FLAGS@";
        const std::string libReplace = "@USER_LIBS@";

        size_t libPos = filecontents.find(libReplace);
        filecontents.replace(libPos, libReplace.length(), libs);

        size_t flagPos = filecontents.find(flagReplace);
        filecontents.replace(flagPos, flagReplace.length(), flags);

        size_t stdPos = filecontents.find(stdReplace);
        filecontents.replace(stdPos, stdReplace.length(), std::to_string(cxx.standard));

        size_t srcPos = filecontents.find(srcReplace);
        filecontents.replace(srcPos, srcReplace.length(), srcFiles);

        size_t installPos = filecontents.find(installReplace);
        filecontents.replace(installPos, installReplace.length(), GetInstallRoot());

        std::ofstream out{execDir / "CMakeLists.txt"};
        out << filecontents;
        out.close();
    }
}
#include "../../headers/Helpers.hpp"

#include "../../headers/FileSystem.hpp"

#include <fstream>
#include <sstream>

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

        std::string srcFiles = replace(metadata.files, " ", "\n\t");
        const std::string& flags = replace(cxx.flags, " ", "\n\t");
        const std::string& libs = replace(cxx.linkLibs, "\" ", "\"\n\t");

        const std::string projectReplace = "@PROJECT_NAME@";
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

        #if defined(_WIN32) || defined(_WIN64)
            for(size_t i = 0; i < srcFiles.size(); i++) {
                if (srcFiles[i] == '\\') {
                    srcFiles.insert(i, 1, '\\');
                    i++;
                }
            }
        #endif

        filecontents.replace(srcPos, srcReplace.length(), srcFiles);

        size_t installPos = filecontents.find(installReplace);

        std::string install_str = GetInstallRoot().string();
        #if defined(_WIN32) || defined(_WIN64)
            for(size_t i = 0; i < install_str.size(); i++) {
                if (install_str[i] == '\\') {
                    install_str.insert(i, 1, '\\');
                    i++;
                }
            }
        #endif
        filecontents.replace(installPos, installReplace.length(), install_str);

        size_t projectPos = filecontents.find(projectReplace);
        filecontents.replace(projectPos, projectReplace.length(), name);

        std::ofstream out{execDir / "CMakeLists.txt"};
        out << filecontents;
        out.close();
    }
}
#include "../../headers/Helpers.hpp"

#include "../../headers/FileSystem.hpp"

#include <fstream>
#include <sstream>

namespace testppCLI {
    void buildCMake(std::string_view name) {
        Metadata metadata = GetMetadata(name);

        if (!metadata.compile) {
            return;
        }

        std::filesystem::path execDir{GetInstallRoot() / "run" / "testpp" / name};
        std::filesystem::path defaultCmake{GetInstallRoot() / "var" / "CMakeLists.txt.in"};

        std::ifstream ifstream{defaultCmake};
        std::string line;
        std::string filecontents;
        filecontents.reserve(150);
        while (std::getline(ifstream, line)) {
            filecontents += line;
            filecontents.push_back('\n');
        }

        CXX cxx = CXX::Deserialize(execDir / "cxx.conf");
        const std::string& srcFiles = replace(metadata.files, " ", "\n\t");
        const std::string& flags = replace(cxx.flags, " ", "\n\t");
        const std::string& libs = replace(cxx.linkLibs, " ", "\n\t");

        const std::string srcReplace = "@USER_SOURCES@";
        const std::string stdReplace = "@CXX_STANDARD@";
        const std::string flagReplace = "@USER_CXX_FLAGS@";
        const std::string libReplace = "@USER_LIBS@";

        size_t libPos = filecontents.find(libReplace);
        filecontents.replace(libPos, libReplace.length(), libs);

        size_t flagPos = filecontents.find(flagReplace);
        filecontents.replace(flagPos, flagReplace.length(), flags);

        std::stringstream stream;
        stream >> cxx.standard;

        size_t stdPos = filecontents.find(stdReplace);
        filecontents.replace(stdPos, stdReplace.length(), stream.str());

        size_t srcPos = filecontents.find(srcReplace);
        filecontents.replace(srcPos, srcReplace.length(), srcFiles);

        std::ofstream out{execDir / "CMakeLists.txt"};
        out << filecontents;
    }
}
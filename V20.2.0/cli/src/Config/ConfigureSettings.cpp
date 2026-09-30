#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"
#include "../../headers/Helpers.hpp"

#include <filesystem>
#include <iostream>

//When configuring cxx stuff, need to set the metadata's compile flag to true
namespace testppCLI {
    void configureFlags(int argc, char** argv) {
        const std::string& lastExec{GetLastExec()};
        if (lastExec.empty()) {
            std::cerr << "Default executable does not exist. Please switch to a different one or create a new one.\n";
            abort();
        }

        std::filesystem::path lastExecDir{lastExec};
        Config config = Config::Deserialize(lastExecDir / "flags.conf");
        
        configConf(config, argc, argv);

        config.Serialize(lastExecDir / "flags.conf");
    }

    void configureCXX(int argc, char** argv) {
        const std::string& lastExec{GetLastExec()};
        if (lastExec.empty()) {
            std::cerr << "Default executable does not exist. Please switch to a different one or create a new one.\n";
            abort();
        }

        std::filesystem::path lastExecDir{lastExec};
        CXX cxx = CXX::Deserialize(lastExecDir / "cxx.conf");
        configCxx(cxx, argc, argv);
        cxx.Serialize(lastExecDir / "cxx.conf");
    }

    void configureLink(int argc, char** argv) {
        const std::string& lastExec{GetLastExec()};
        if (lastExec.empty()) {
            std::cerr << "Default executable does not exist. Please switch to a different one or create a new one.\n";
            abort();
        }

        std::filesystem::path lastExecDir{lastExec};
        CXX cxx = CXX::Deserialize(lastExecDir / "cxx.conf");
        configLibs(cxx, argc, argv);
        cxx.Serialize(lastExecDir / "cxx.conf");
    }
}
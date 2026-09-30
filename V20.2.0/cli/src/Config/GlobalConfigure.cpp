#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"
#include "../../headers/Helpers.hpp"

#include <filesystem>
#include <iostream>

//When configuring cxx stuff, need to set the metadata's compile flag to true
namespace testppCLI {
    void globalConfigureFlags(int argc, char** argv) {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path flags{iter.path() / "flags.conf"};
                
                Config config = Config::Deserialize(flags);
                configConf(config, argc, argv);
                config.Serialize(flags);
            }
        }

        Config globalConfig = Config::Deserialize(run / "global_flags.conf");
        configConf(globalConfig, argc, argv);
        globalConfig.Serialize(run / "global_flags.conf");
    }
    
    void globalConfigureCXX(int argc, char** argv) {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX cxx = CXX::Deserialize(cxxPath);
                configCxx(cxx, argc, argv);
                cxx.Serialize(iter.path() / "cxx.conf");
            }
        }

        CXX globalCXX = CXX::Deserialize(run / "global_cxx.conf");
        configCxx(globalCXX, argc, argv);
        globalCXX.Serialize(run / "global_cxx.conf");
    }

    void globalConfigureLink(int argc, char** argv) {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX cxx = CXX::Deserialize(cxxPath);
                configLibs(cxx, argc, argv);
                cxx.Serialize(iter.path() / "cxx.conf");
            }
        }

        CXX globalCXX = CXX::Deserialize(run / "global_cxx.conf");
        configLibs(globalCXX, argc, argv);
        globalCXX.Serialize(run / "global_cxx.conf");
    }
}
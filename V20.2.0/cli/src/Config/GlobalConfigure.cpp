#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"
#include "../../headers/Helpers.hpp"

#include <filesystem>
#include <iostream>

namespace testppCLI {
    void globalConfigureFlags(int begin, int end, char** argv) {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};

        std::vector<char*> newArgv;
        newArgv.reserve(end - begin + 2);
        newArgv.push_back(argv[0]);
        newArgv.push_back(argv[1]);
        for (; begin < end; begin++) {
            newArgv.push_back(argv[begin]);
        }
        newArgv.push_back(nullptr);
        int argc = newArgv.size() - 1;

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path flags{iter.path() / "flags.conf"};
                
                Config config = Config::Deserialize(flags);
                configConf(config, argc, newArgv.data());
                config.Serialize(flags);
            }
        }

        Config globalConfig = Config::Deserialize(run / "global_flags.conf");
        configConf(globalConfig, argc, newArgv.data());
        globalConfig.Serialize(run / "global_flags.conf");
    }
    
    void globalConfigureCXX(int begin, int end, char** argv) {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};

        std::vector<char*> newArgv;
        newArgv.reserve(end - begin + 2);
        newArgv.push_back(argv[0]);
        newArgv.push_back(argv[1]);
        for (; begin < end; begin++) {
            newArgv.push_back(argv[begin]);
        }
        newArgv.push_back(nullptr);
        int argc = newArgv.size() - 1;

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX cxx = CXX::Deserialize(cxxPath);
                configCxx(cxx, argc, newArgv.data());
                cxx.Serialize(iter.path() / "cxx.conf");

                Metadata meta = Metadata::Deserialize(iter.path() / "meta.data");
                meta.compile = true;
                meta.Serialize(iter.path() / "meta.data");
            }
        }

        CXX globalCXX = CXX::Deserialize(run / "global_cxx.conf");
        configCxx(globalCXX, argc, newArgv.data());
        globalCXX.Serialize(run / "global_cxx.conf");
    }

    void globalConfigureLink(int begin, int end, char** argv) {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};

        std::vector<char*> newArgv;
        newArgv.reserve(end - begin + 2);
        newArgv.push_back(argv[0]);
        newArgv.push_back(argv[1]);
        for (; begin < end; begin++) {
            newArgv.push_back(argv[begin]);
        }
        newArgv.push_back(nullptr);
        int argc = newArgv.size() - 1;

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX cxx = CXX::Deserialize(cxxPath);
                configLibs(cxx, argc, newArgv.data());
                cxx.Serialize(iter.path() / "cxx.conf");

                Metadata meta = Metadata::Deserialize(iter.path() / "meta.data");
                meta.compile = true;
                meta.Serialize(iter.path() / "meta.data");
            }
        }

        CXX globalCXX = CXX::Deserialize(run / "global_cxx.conf");
        configLibs(globalCXX, argc, newArgv.data());
        globalCXX.Serialize(run / "global_cxx.conf");
    }
}
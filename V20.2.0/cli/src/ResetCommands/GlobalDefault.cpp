#include "../../headers/ResetCommands.hpp"

#include "../../headers/FileSystem.hpp"
#include "../../headers/Configure.hpp"
#include <filesystem>

//When configuring cxx stuff, need to set the metadata's compile flag to true
namespace testppCLI {
    void globalDefaultReset() {
        globalDefaultFlags();

        std::filesystem::path run{GetInstallRoot() / "run" / "testpp"};
        std::filesystem::path var{GetInstallRoot() / "var"};

        std::filesystem::path dCxx{var / "default_cxx.conf"};
        
        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                std::filesystem::remove(cxxPath);
                std::filesystem::copy_file(dCxx, cxxPath);
            }
        }

        std::filesystem::path gCxx{run / "global_cxx.conf"};
        std::filesystem::remove(gCxx);
        std::filesystem::copy_file(dCxx, gCxx);
    }

    void globalDefaultFlags() {
        std::filesystem::path run{GetInstallRoot() / "run" / "testpp"};
        std::filesystem::path var{GetInstallRoot() / "var"};

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path flagPath{iter.path() / "flags.conf"};
                std::filesystem::remove(flagPath);
                std::filesystem::copy_file(var / "default_flag.conf", flagPath);
            }
        }
        
        std::filesystem::remove(run / "global_flags.conf");
        std::filesystem::copy_file(var / "default_flag.conf", run / "global_flags.conf");
    }

    void globalDefaultCxx() {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};
        std::filesystem::path var{installRoot / "var"};

        CXX dCxx = CXX::Deserialize(var / "default_cxx.conf");

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX lCxx = CXX::Deserialize(cxxPath);
                lCxx.flags = dCxx.flags;
                lCxx.standard = dCxx.standard;

                lCxx.Serialize(cxxPath);
            }
        }

        CXX gCxx = CXX::Deserialize(run / "global_cxx.conf");
        gCxx.flags = dCxx.flags;
        gCxx.standard = dCxx.standard;
        gCxx.Serialize(run / "global_cxx.conf");
    }

    void globalDefaultLink() {
        std::filesystem::path run{GetInstallRoot() / "run" / "testpp"};
        std::filesystem::path var{GetInstallRoot() / "var"};

        CXX dCxx = CXX::Deserialize(var / "default_cxx.conf");

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX lCxx = CXX::Deserialize(cxxPath);
                lCxx.linkLibs = dCxx.linkLibs;

                lCxx.Serialize(cxxPath);
            }
        }

        CXX gCxx = CXX::Deserialize(run / "global_cxx.conf");
        gCxx.linkLibs = dCxx.linkLibs;
        gCxx.Serialize(run / "global_cxx.conf");
    }
}
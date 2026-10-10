#include "../../headers/ResetCommands.hpp"

#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"

#include <filesystem>
#include <fstream>

//When configuring cxx stuff, need to set the metadata's compile flag to true
namespace testppCLI {
    void globalReset() {
        globalResetFlags();

        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};
        std::filesystem::path var{installRoot / "var"};

        std::filesystem::path gCxx{run / "global_cxx.conf"};

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};

                std::filesystem::remove(cxxPath);
                std::filesystem::copy_file(gCxx, cxxPath);
            }
        }
    }

    void globalResetFlags() {
        std::filesystem::path run{GetInstallRoot() / "run" / "testpp"};
        std::filesystem::path var{GetInstallRoot() / "var"};

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path flagPath{iter.path() / "flags.conf"};
                std::filesystem::remove(flagPath);
                std::filesystem::copy_file(run / "global_flags.conf", flagPath);
            }
        }
    }

    void globalResetCxx() {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};
        std::filesystem::path var{installRoot / "var"};

        CXX gCxx = CXX::Deserialize(run / "global_cxx.conf");

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX lCxx = CXX::Deserialize(cxxPath);
                lCxx.flags = gCxx.flags;
                lCxx.standard = gCxx.standard;

                lCxx.Serialize(cxxPath);
            }
        }
    }

    void globalResetLink() {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};
        std::filesystem::path var{installRoot / "var"};

        CXX gCxx = CXX::Deserialize(run / "global_cxx.conf");

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX lCxx = CXX::Deserialize(cxxPath);
                lCxx.linkLibs = gCxx.linkLibs;

                lCxx.Serialize(cxxPath);
            }
        }
    }

    void globalResetInclude() {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};
        std::filesystem::path var{installRoot / "var"};

        CXX gCxx = CXX::Deserialize(run / "global_cxx.conf");

        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::filesystem::path cxxPath{iter.path() / "cxx.conf"};
                CXX lCxx = CXX::Deserialize(cxxPath);
                lCxx.include = gCxx.include;

                lCxx.Serialize(cxxPath);
            }
        }
    }
}
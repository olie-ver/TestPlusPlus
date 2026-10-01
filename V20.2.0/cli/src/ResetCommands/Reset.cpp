#include "../../headers/ResetCommands.hpp"

#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"

#include <filesystem>
#include <fstream>

namespace testppCLI {
    void reset() {
        resetFlags();

        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path run{GetInstallRoot() / "run" / "testpp"};

        CXX cxx = CXX::Deserialize(curExecDir / "cxx.conf");
        CXX gCxx = CXX::Deserialize(run / "global_cxx.conf");

        cxx.flags = gCxx.flags;
        cxx.standard = gCxx.standard;
        cxx.linkLibs = gCxx.linkLibs;
        cxx.Serialize(curExecDir / "cxx.conf");
    }

    void resetFlags() {
        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path run{GetInstallRoot() / "run" / "testpp"};

        std::filesystem::remove(curExecDir / "flags.conf");

        std::filesystem::copy_file(run / "global_flags.conf", curExecDir / "flags.conf");
    }

    void resetCxx() {
        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path run{GetInstallRoot() / "run" / "testpp"};

        CXX cxx = CXX::Deserialize(curExecDir / "cxx.conf");
        CXX gCxx = CXX::Deserialize(run / "global_cxx.conf");

        cxx.flags = gCxx.flags;
        cxx.standard = gCxx.standard;
        cxx.Serialize(curExecDir / "cxx.conf");
    }

    void resetLink() {
        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path run{GetInstallRoot() / "run" / "testpp"};

        CXX cxx = CXX::Deserialize(curExecDir / "cxx.conf");
        CXX gCxx = CXX::Deserialize(run / "global_cxx.conf");

        cxx.linkLibs = gCxx.linkLibs;
        cxx.Serialize(curExecDir / "cxx.conf");
    }
}
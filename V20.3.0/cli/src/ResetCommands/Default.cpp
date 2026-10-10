#include "../../headers/ResetCommands.hpp"

#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"
#include <filesystem>

//When configuring cxx stuff, need to set the metadata's compile flag to true
namespace testppCLI {
    void defaultReset() {
        defaultFlags();

        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path var{GetInstallRoot() / "var"};

        std::filesystem::remove(curExecDir / "cxx.conf");
        std::filesystem::copy_file(var / "default_cxx.conf", curExecDir / "cxx.conf");
    }

    void defaultFlags() {
        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path var{GetInstallRoot() / "var"};

        std::filesystem::remove(curExecDir / "flags.conf");
        std::filesystem::copy_file(var / "default_flag.conf", curExecDir / "flags.conf");
    }

    void defaultCxx() {
        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path var{GetInstallRoot() / "var"};

        CXX dCxx{CXX::Deserialize(var / "default_cxx.conf")};

        CXX curCxx{CXX::Deserialize(curExecDir / "cxx.conf")};
        curCxx.flags = dCxx.flags;
        curCxx.standard = dCxx.standard;
        curCxx.Serialize(curExecDir / "cxx.conf");
    }

    void defaultLink() {
        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path var{GetInstallRoot() / "var"};

        CXX dCxx{CXX::Deserialize(var / "default_cxx.conf")};

        CXX curCxx{CXX::Deserialize(curExecDir / "cxx.conf")};
        curCxx.linkLibs = dCxx.linkLibs;
        curCxx.Serialize(curExecDir / "cxx.conf");
    }

    void defaultInclude() {
        std::filesystem::path curExecDir{GetLastExec()};
        std::filesystem::path var{GetInstallRoot() / "var"};
        CXX dCxx{CXX::Deserialize(var / "default_cxx.conf")};

        CXX curCxx{CXX::Deserialize(curExecDir / "cxx.conf")};
        curCxx.include = dCxx.include;
        curCxx.Serialize(curExecDir / "cxx.conf");
    }
}
#include "../../headers/PrintCommands.hpp"

#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"

#include <iostream>

namespace testppCLI {
    void inspect(int argc, char** argv) {
        std::filesystem::path curExecDir;
        if (argc == 2) {
            curExecDir = GetLastExec();
        } else if (argc == 3) {
            std::filesystem::path curExecDir{GetInstallRoot() / "run" / "testpp" / argv[2]};
        } else {
            std::cerr << "Invalid usage. Expected usage is: \"testpp --inspect [name]\" where [name is optional]\n";
            abort();
        }

        if (curExecDir.empty()) {
            std::cerr << "No current executable to inspect. Please set the default executable\n";
            abort();
        }

        std::cout << "Executable Name: ";
        std::cout << curExecDir.filename() << "\n\n";

        std::cout << "Configuration Flags:";
        Config conf = Config::Deserialize(curExecDir / "flags.conf");

        std::cout << "\n\tnum_threads = " << conf.num_threads;
        std::cout << "\n\tverbosity = " << conf.verbosity;
        std::cout << "\n\ttimeout = " << conf.timeout;
        std::cout << "\n\ttime_unit = " << conf.timeUnit;
        std::cout << "\n\tstdoutSize = " << conf.stdoutSize;
        std::cout << "\n\tstderrSize = " << conf.stderrSize;
        std::cout << "\n\tstreaming: ";

        if (conf.stream) {
            std::cout << "On";
        } else {
            std::cout << "Off";
        }

        std::cout << "\n\tjsonFile: ";
        if (conf.jsonFile == "") {
            std::cout << "no file";
        } else {
            std::cout << conf.jsonFile;
        }

        std::cout << "\n\tjUnitFile: ";
        if (conf.jUnitFile == "") {
            std::cout << "no file";
        } else {
            std::cout << conf.jUnitFile;
        }

        std::cout << "\n\tskipSuites: ";
        if (conf.skipSuites == "") {
            std::cout << "no suites to skip";
        } else {
            std::cout << conf.skipSuites;
        }

        std::cout << "\n\ttestOnlySuites: ";
        if (conf.testOnlySuites == "") {
            std::cout << "no suites to only test";
        } else {
            std::cout << conf.testOnlySuites;
        }

        CXX cxx = CXX::Deserialize(curExecDir / "cxx.conf");

        std::cout << "\n\ncxx_flags: " << cxx.flags;
        std::cout << "\ncxx standard: " << "-std=c++" << std::to_string(cxx.standard);
        std::cout << "\nlink libraries: " << cxx.linkLibs;

        Metadata meta = Metadata::Deserialize(curExecDir / "meta.data");
        std::cout << "\n\nMetadata:";
        std::cout << "\nNeeds Compile: " << std::to_string(meta.compile);
        std::cout << "\nSource Files: " << meta.files << std::endl;
    }
}
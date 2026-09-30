#include "../../headers/PrintCommands.hpp"

#include "../../headers/FileSystem.hpp"

#include <iostream>
#include <filesystem>

namespace testppCLI {
    void diagnostics() {
        std::cout << "Test++ Version: " << VERSION << "\n\n";
        std::cout << "Installation Root: " << GetInstallRoot() << "\n\n";

        listExecs();

        std::cout << "\nGlobal Configuration Flags:";
        Config conf = Config::Deserialize(GetInstallRoot() / "run" / "testpp" / "global_flags.conf");

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

        CXX cxx = CXX::Deserialize(GetInstallRoot() / "run" / "testpp" / "global_cxx.conf");

        std::cout << "\n\ncxx_flags: " << cxx.flags;
        std::cout << "\ncxx standard: " << "-std=c++" << std::to_string(cxx.standard);
        std::cout << "\nlink libraries: " << cxx.linkLibs << std::endl;
    }
}
#include "../../headers/Helpers.hpp"

#include <iostream>

namespace testppCLI {
    void configConf(Config& config, int argc, char** argv) {
        for (int i = 2; i < argc; i++) {
            std::string arg{argv[i]};

            if (arg.starts_with("--v=") || arg.starts_with("--verbosity=")) {
                std::string substr = arg.substr(arg.find('=') + 1);
                config.verbosity = substr;
            } else if (arg.starts_with("--t=") || arg.starts_with("--numthreads=") || arg.starts_with("--threads=")) {
                std::string substr{arg.substr(arg.find('=') + 1)};
                int numThreads = stoi(substr);
                if (numThreads < 1) {
                    numThreads = 1;
                }
                config.num_threads = numThreads;
            } else if (arg.starts_with("--timeout=") || arg.starts_with("--timeout_sec=")) {
                std::string substr{arg.substr(arg.find('=') + 1)};
                config.timeout = stoi(substr);
                config.timeUnit = Config::sec;
            } else if (arg.starts_with("--timeout_ms=")) {
                std::string substr{arg.substr(arg.find('=') + 1)};
                config.timeout = stoi(substr);
                config.timeUnit = Config::ms;
            } else if (arg.starts_with("--s=") || arg.starts_with("--skip=")) {
                std::string substr = arg.substr(arg.find('=') + 1);
                config.skipSuites = substr;
            } else if (arg.starts_with("--testonly=") || arg.starts_with("--test_only=") || arg.starts_with("--to") || arg.starts_with("--t_o=")) {
                std::string substr = arg.substr(arg.find('=') + 1);
                config.testOnlySuites = substr;
            } else if (arg == "--json") {
                i++;
                std::string file = argv[i];
                if (!file.ends_with(".json")) {
                    std::cerr << "JSON file does not in .json extension\n";
                    abort(); 
                }
                config.jsonFile = file;
            } else if (arg == "--junit" || arg == "--xml") {
                i++;
                std::string file = argv[i];
                if (!file.ends_with(".xml")) {
                    std::cerr << "XML file does not in .xml extension\n";
                    abort(); 
                }
                config.jUnitFile = file;
            } else if (arg.starts_with("--stdout=") || arg.starts_with("--stdoutsize=")) {
                std::string substr(arg.substr(arg.find('=') + 1));
                int size = stoi(substr);
                if (size < 0) {
                    std::cerr << "stdoutsize must be nonnegative";
                    abort();
                }
                config.stdoutSize = stoi(substr);
            } else if (arg.starts_with("--stderr=") || arg.starts_with("--stderrsize=")) {
                std::string substr(arg.substr(arg.find('=') + 1));
                int size = stoi(substr);
                if (size < 0) {
                    std::cerr << "stderrsize must be nonnegative";
                    abort();
                }
                config.stderrSize = size;
            } else if (arg == "--truncate") {
                config.stdoutSize = 1024;
                config.stderrSize = 1024;
            } else if (arg == "--stream") {
                config.stream = !config.stream;
            }
        }
    }

    void configCxx(CXX& cxx, int argc, char** argv) {
        std::string flags;

        for (int i = 2; i < argc; i++) {
            std::string arg{argv[i]};
            if (arg.starts_with("-std=c++")) {
                std::string substr{arg.substr(arg.find("c++") + 3)};
                int std = stoi(substr);
                if (std != 98 && std != 3 && std != 11 && std != 14 && std != 17 && std != 20 && std != 23 && std != 26) {
                    std::cerr << "Invalid C++ standard. Valid standards are: 98, 03, 11, 14, 17, 20, 23, and 26\n";
                    abort();
                }
                cxx.standard = std;
            } else {
                flags += arg;
                flags += ' ';
            }
        }

        cxx.flags = flags;
    }

    void configLibs(CXX& cxx, int argc, char** argv) {
        std::string libs;

        for (int i = 2; i < argc; i++) {
            std::string arg{argv[i]};
            libs += arg;
            libs += ' ';
        }
        cxx.linkLibs = libs;
    } 
}
#include "../headers/CLI.hpp" 
#include "../headers/Data.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

namespace tppCLI {
    void CreateConfig(std::filesystem::path path, int argc, char** argv) {
        //read in the current config settings
        Config config = GetConfig(path);
        size_t pos{};

        for (int i = 2; i < argc; i++) {
            std::string flag(argv[i]);
            std::transform(flag.begin(), flag.end(), flag.begin(), [](unsigned char c) { return std::tolower(c); });

            if (std::any_of(verbArgs.begin(), verbArgs.end(), [&flag](std::string_view flagType){ return flag.starts_with(flagType); })) {
                std::string arg = flag.substr(flag.find('=') + 1);

                if (std::find(validArgs.begin(), validArgs.end(), arg) != validFlags.end()) {
                    config.verbosity = arg;
                } else {
                    std::cerr << "Unknown verbosity flag: " << arg << "\nSupported verbosity flags are:\n";

                    for (size_t i = 0; i < validArgs.size(); i++) {
                        std::cerr << validArgs[i] << '\n';
                    }
                    
                    std::abort();  
                }
            } else if (std::any_of(threadArgs.begin(), threadArgs.end(), [&flag](std::string_view flagType){ return flag.starts_with(flagType); })) {
                std::string arg = flag.substr(flag.find('=') + 1);

                try {
                    config.num_threads = stoi(arg, &pos);
                } catch (const std::exception& ex) {
                    std::cerr << "Caught std::exception " << ex.what() << '\n';
                    std::abort();
                }
            } else if (std::any_of(skipArgs.begin(), skipArgs.end(), [&flag](std::string_view flagType){ return flag.starts_with(flagType); })) {
                std::string originalFlag(argv[i]);
                std::string arg = originalFlag.substr(originalFlag.find('=') + 1);

                config.skipSuites = arg;
            } else if (std::any_of(testArgs.begin(), testArgs.end(), [&flag](std::string_view flagType){ return flag.starts_with(flagType); })) {
                std::string originalFlag(argv[i]);
                std::string arg = originalFlag.substr(originalFlag.find('=') + 1);
                
                config.testOnlySuites = arg;
            } else if (std::any_of(timeArgs.begin(), timeArgs.end(), [&flag](std::string_view flagType){ return flag.starts_with(flagType); })) {
                if (flag.find("_ms=") != std::string::npos) {
                    config.time_unit = "ms";
                }

                std::string arg = flag.substr(flag.find('=') + 1);

                try {
                    config.timeout = std::stoi(arg, &pos);
                    if (config.timeout < 0) {
                        std::cerr << "timeout duration must be nonnegative" << std::endl;
                        std::abort();
                    }
                } catch (const std::exception& ex) {
                    std::cerr << "Caught std::exception " << ex.what() << '\n';
                    std::abort();
                }
            } else if (flag == "--json") {
                if (i != argc - 1) {
                    config.jsonFile = argv[++i];
                    if (!config.jsonFile.ends_with(".json")) {
                        std::cerr << "Invalid .json path: " << config.jsonFile << std::endl;
                        std::abort();
                    }
                } else {
                    std::cerr << "Missing .json file path after --json flag" << std::endl;
                    std::abort();
                }
            } else if (flag == "--junit" || flag == "--xml") {
                if (i != argc - 1) {
                    config.jUnitFile = argv[++i];
                    if (!config.jUnitFile.ends_with(".xml")) {
                        std::cerr << "Invalid .xml path: " << config.jUnitFile << std::endl;
                        std::abort();
                    }
                } else {
                    std::cerr << "Missing .xml file path after --junit/--xml flag" << std::endl;
                    std::abort();
                }
            } else if (flag.find("--stdoutsize=") != std::string::npos 
                || flag.find("--stdout=") != std::string::npos)
            {
                std::string arg = flag.substr(flag.find('=') + 1);

                try {
                    config.stdoutSize = std::stoi(arg, &pos);
                    if (config.stdoutSize < 0) {
                        std::cerr << "stdout output length must be nonnegative" << std::endl;
                        std::abort();
                    }
                } catch (const std::exception& ex) {
                    std::cerr << "Caught std::exception " << ex.what() << '\n';
                    std::abort();
                }
            } else if (flag.find("--stderrsize=") != std::string::npos 
                || flag.find("--stderr=") != std::string::npos)
            {  std::string arg = flag.substr(flag.find('=') + 1);

                try {
                    config.stderrSize = std::stoi(arg, &pos);
                    if (config.stderrSize < 0) {
                        std::cerr << "stdout output length must be nonnegative" << std::endl;
                        std::abort();
                    }
                } catch (const std::exception& ex) {
                    std::cerr << "Caught std::exception " << ex.what() << '\n';
                    std::abort();
                }
            } else if (flag == "--truncate") {
                config.stdoutSize = 1024;
                config.stderrSize = 1024;
            } else if (flag.find("--stream=") != std::string::npos) {
                std::string arg = flag.substr(flag.find('=') + 1);
                config.stream = arg == "true";
            } else if (flag == "--stream") {
                config.stream = true;
            }
        }

        std::ofstream configFile(path, std::ios::out | std::ios::trunc);

        configFile << "--numthreads=" << config.num_threads;
        configFile << " --timeout";
        if (config.time_unit == "ms") {
            configFile << "_ms";
        }
        configFile << "=" << config.timeout;

        if (config.verbosity != "") {
            configFile << " --verbosity=" << config.verbosity;
        }

        if (config.jsonFile != "") {
            configFile <<  " --json " << config.jsonFile;
        }

        if (config.jUnitFile != "") {
            configFile << " --junit " << config.jUnitFile;
        }
        
        if (config.skipSuites != "") {
            configFile << " --skip=" << config.skipSuites;
        }

        if (config.testOnlySuites != "") {
            configFile << " --testonly=" << config.testOnlySuites;
        }

        configFile << " --stdoutsize=" << config.stdoutSize;
        configFile << " --stderrsize=" << config.stderrSize;

        if (config.stream) {
            configFile << " --stream";
        }
    }

    const Config GetConfig(std::filesystem::path path)
    {
        Config config;

        std::ifstream file(path);
        std::string flag;
        size_t pos{};

        while (file >> flag)
        {
            if (flag.find("--v=") != std::string::npos || flag.find("--verbosity=") != std::string::npos) {
                config.verbosity = flag.substr(flag.find('=') + 1);
            }
            else if (flag.find("--numthreads=") != std::string::npos) {
                config.num_threads = std::stoi(flag.substr(flag.find('=') + 1), &pos);
            }
            else if (flag.find("--skip=") != std::string::npos) {
                config.skipSuites = flag.substr(flag.find('=') + 1);
            }
            else if (flag.find("--testonly=") != std::string::npos) {
                config.testOnlySuites = flag.substr(flag.find('=') + 1);
            }
            else if (flag.find("--timeout") != std::string::npos && flag.find('=') != std::string::npos) {
                config.time_unit = (flag.find("_ms=") != std::string::npos) ? "ms" : "sec";
                config.timeout = std::stoi(flag.substr(flag.find('=') + 1), &pos);
            }
            else if (flag == "--json") {
                file >> config.jsonFile;
            }
            else if (flag == "--junit" || flag == "--xml") {
                file >> config.jUnitFile;
            }
            else if (flag.find("--stdoutsize=") != std::string::npos) {
                config.stdoutSize = std::stoi(flag.substr(flag.find('=') + 1), &pos);
            }
            else if (flag.find("--stderrsize=") != std::string::npos) {
                config.stderrSize = std::stoi(flag.substr(flag.find('=') + 1), &pos);
            }
            else if (flag == "--truncate") {
                config.stdoutSize = 1024;
                config.stderrSize = 1024;
            }
            else if (flag == "--stream") {
                config.stream = true;
            }
        }

        return config;
    }

    const CXX getCXX(const std::filesystem::path &path)
    {
        std::ifstream readCxx(path);
        std::string line;

        CXX cxx;

        while (std::getline(readCxx, line))
        {
            std::istringstream iss(line);
            if (line.find("Flags:") != std::string::npos) {
                cxx.flags = line.substr(7);
            } else if (line.find("Standard:") != std::string::npos) {
                cxx.standard = line.substr(line.size() - 2);
            }
        }

        return cxx;
    }
}
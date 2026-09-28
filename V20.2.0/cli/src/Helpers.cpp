#include "../headers/Helpers.hpp"
#include "../headers/CLI.hpp"

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#if defined(_WIN32) || defined(_WIN64)
    #include <algorithm>
#endif

namespace tppHelpers {
    void printDiagnostics(const char* VERSION, 
        const std::filesystem::path& installRoot, 
        const std::filesystem::path& user_exec,
        const tppCLI::CXX& user_cxx,
        const tppCLI::Config& settings
    )
    {
        std::cout << "Version: " << VERSION << "\n\n";
        std::cout << "Installation Folder: " << installRoot << "\n\n";

        std::cout << "Test Executable Built: ";

        bool user_exec_exists = std::filesystem::exists(user_exec);

        if (user_exec_exists) {
            std::cout << "True\n";
            std::cout << "Test Executable Path: " << user_exec.string() << "\n\n";
        } else {
            std::cout << "False\n\n";
        }

        std::cout << "Configurations:";
        std::cout << "\n\tnum_threads = " << settings.num_threads;
        std::cout << "\n\tverbosity = " << settings.verbosity;
        std::cout << "\n\ttimeout = " << settings.timeout;
        std::cout << "\n\ttime_unit = " << settings.time_unit;
        std::cout << "\n\tstdoutSize = " << settings.stdoutSize;
        std::cout << "\n\tstderrSize = " << settings.stderrSize;
        std::cout << "\n\tstreaming: ";

        if (settings.stream) {
            std::cout << "On";
        } else {
            std::cout << "Off";
        }

        std::cout << "\n\tjsonFile: ";
        if (settings.jsonFile == "") {
            std::cout << "no file";
        } else {
            std::cout << settings.jsonFile;
        }

        std::cout << "\n\tjUnitFile: ";
        if (settings.jUnitFile == "") {
            std::cout << "no file";
        } else {
            std::cout << settings.jUnitFile;
        }

        std::cout << "\n\tskipSuites: ";
        if (settings.skipSuites == "") {
            std::cout << "no suites to skip";
        } else {
            std::cout << settings.skipSuites;
        }

        std::cout << "\n\ttestOnlySuites: ";
        if (settings.testOnlySuites == "") {
            std::cout << "no suites to only test";
        } else {
            std::cout << settings.testOnlySuites;
        }

        std::cout << "\n\ncxx_flags: " << user_cxx.flags;
        std::cout << "\ncxx standard: " << "-std=c++" << user_cxx.standard;

        std::cout << std::endl;
    }

    void getFilesAndArgs(int argc, char** argv,
        std::vector<std::string>& args, 
        std::vector<std::filesystem::path>& files
    ) 
    {
        for (int i = 1; i < argc; i++) {
            std::filesystem::path p(argv[i]);

            if (std::filesystem::is_regular_file(p))
            {
                files.push_back(std::filesystem::absolute(p));
            } 
            else if (std::filesystem::is_directory(p))
            {
                for (const auto& entry :
                    std::filesystem::recursive_directory_iterator(p))
                {
                    if (entry.path().extension() == ".cpp" || entry.path().extension() == ".cc")
                    {
                        files.push_back(std::filesystem::absolute(entry.path()));
                    }
                }
            } else {
                args.push_back(p.string());
            }
        }
    }

    void printHelp() {
        std::cout << 
        "help:\n"
        "commands:\n"
        "\ttestpp --help - prints out information on how to use Test++\n"
        "\ttestpp --version - prints out the version of Test++\n"
        "\ttestpp --diagnostics - prints out information about your version of Test++"
        " as well as your settings\n\n"

        "\ttestpp - runs the last built executable, if there is one\n"
        "\ttestpp [files/directories] - adds files to the generated executable and runs it\n"
        "\ttestpp [flags] - runs the last built executable under the specified flags\n"
        "\ttestpp [pattern] - a combination of the above two commands where [pattern] is"
                                         " a set of files/directories and flags\n\n"

        "\ttestpp --reset - resets both your configuration and compiler flag settings\n"
        "\ttestpp --reset-flags - resets only your configuration settings\n"
        "\ttestpp --reset-cxx - resets only your compiler flag settings\n"

        "\ttestpp config [flags] - configures your Test++ settings\n"
        "\ttestpp cxx_flags [compiler_flags] - configures your Test++ compiler flags."
                            "\n\t\tType them in as if you were passing them directly to the compiler\n\n"
        
        "Supported [flags]:\n"
        "\tVerbosity: --v= or --verbosity=\n"
        "\tThreads: --t= or --numthreads= or --threads=\n"
        "\tTimeout: --timeout= or --timeout_sec= or --timeout_ms=\n"
        "\tSkip Suites: --s= or --skip=\n"
        "\tTest Only Suites: --testonly= or --test_only= or --to= or t_o=\n\n"
        "\tJSON Output: --json PATH_TO_FILE\n"
        "\tXML Output: --junit PATH_TO_FILE or --xml PATH_TO_FILE\n"
        "\tstdout output length: --stdoutsize= or --stdout=\n"
        "\tstderr output length: --stderrsize= or --stderr=\n"
        "\tstdout and stderr output length (1024 chars): --truncate\n"
        "\tStream Progress: --stream\n"
        "\nSuites being skipped must be separated by ',' with NO space in between\n"
        "\nSupported verbosity flags: default, minimum, passonly, failonly, failonlymin\n"

        << std::flush;
    }

    void generateCMake(
        const std::filesystem::path& install_prefix,
        const std::filesystem::path& write_loc,
        const std::filesystem::path& cmake_template, 
        const std::vector<std::filesystem::path>& files,
        const tppCLI::CXX& cxxFlags
    ) 
    {
        const std::string installReplace = "@INSTALL_PREFIX@";
        const std::string replace = "@USER_SOURCES@";
        const std::string cxxReplace = "@USER_CXX_FLAGS@";
        const std::string stdReplace = "@CXX_STANDARD@";
        const std::string libReplace = "@USER_LIBS@";

        std::ifstream readCmakeTemplate(cmake_template);
        std::stringstream cmake;
        cmake << readCmakeTemplate.rdbuf();
        std::string generate_executable(cmake.str());

        std::ostringstream imploded;
        for (size_t i = 0; i < files.size(); i++) {
            imploded << files[i] << "\n\t";
        }

        std::string install_str = install_prefix.string();
        std::string imploded_str = imploded.str();

        imploded.clear();
        size_t pos;
        std::string libraries = cxxFlags.libraries;
        std::string lib;
        while ((pos = cxxFlags.libraries.find(',')) != std::string::npos) {
            lib = libraries.substr(0, pos);
            imploded << lib << '\n\t';
            libraries.erase(0UL, pos + 1);
        }
        imploded << libraries;
        std::string lib_str = imploded.str();

        #if defined(_WIN32) || defined(_WIN64)
            for(size_t i = 0; i < install_str.size(); i++) {
                if (install_str[i] == '\\') {
                    install_str.insert(i, 1, '\\');
                    i++;
                }
            }
        #endif

        generate_executable.replace(
            generate_executable.find(installReplace),
            installReplace.size(),
            install_str
        );

        generate_executable.replace(
            generate_executable.find(replace),
            replace.size(),
            imploded_str
        );

        generate_executable.replace(
            generate_executable.find(cxxReplace),
            cxxReplace.size(),
            cxxFlags.flags
        );

        generate_executable.replace(
            generate_executable.find(stdReplace),
            stdReplace.size(),
            cxxFlags.standard
        );

        generate_executable.replace(
            generate_executable.find(libReplace),
            libReplace.size(),
            lib_str
        );

        std::ofstream out(write_loc);
        out << generate_executable;
        out.close();
    }

    bool configureAndBuild(const std::filesystem::path& run) {    
        std::string build_dir = run.string();

        std::string configure = "cmake -S \"" + build_dir +  "\" -B \"" + build_dir + "\"";

        int configResult = std::system(configure.c_str());

        if (configResult != 0) {
            std::cerr << "Failed to configure project" << std::endl;
            return false;
        }

        #if defined(_WIN32) || defined(_WIN64)
            std::string build = "cmake --build \"" + build_dir + "\" --config Release";
        #else
            std::string build = "cmake --build \"" + build_dir + "\"";
        #endif

        int buildResult = std::system(build.c_str());

        if (buildResult != 0) {
            std::cerr << "Failed to build project" << std::endl;
            return false;
        }

        return true;
    }
}
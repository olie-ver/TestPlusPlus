#include "../../headers/PrintCommands.hpp"

#include <iostream>

namespace testppCLI {
    void help() {
        std::cout << 
        "help:\n"
        "commands:\n"
        "\ttestpp --help / testpp --h - prints out information on how to use Test++\n"
        "\ttestpp --version / testpp --v - prints out the version of Test++\n"
        "\ttestpp --diagnostics / testpp --d - prints out information about your version of Test++"
        " as well as your settings\n\n"

        "\ttestpp - runs the last built executable, if there is one\n"
        "\ttestpp [files/directories] - adds files to the generated executable and runs it\n"
        "\ttestpp [flags] - runs the last built executable under the specified flags\n"
        "\ttestpp [pattern] - a combination of the above two commands where [pattern] is"
                                         " a set of files/directories and flags\n\n"

        "\ttestpp --reset - resets both your configuration and compiler flag settings to the global settings\n"
        "\ttestpp --reset-flags - resets only your configuration settings to the global settings\n"
        "\ttestpp --reset-cxx - resets only your compiler flag settings to the global settings\n"
        "\ttestpp --reset-link - resets only your linked libraries to the global settings\n"
        "\ttestpp --resets-link - resets only your includes paths to the global settings\n"
        "\t - Add \"--g\" or \"--global\" to the beginning or the end to these commands to run this command globally\n\n"

        "\ttestpp --default - resets both your configuration and compiler flag settings to the default settings\n"
        "\ttestpp --default-flags - resets only your configuration settings to the default settings\n"
        "\ttestpp --default-cxx - resets only your compiler flag settings to the default settings\n"
        "\ttestpp --default-link - resets only your linked libraries to the default settings\n"
        "\ttestpp --default-include - resets only include paths to the default settings\n"
        "\t - Add \"--g\" or \"--global\" to the beginning or the end to these commands to run this command globally\n\n"

        "\ttestpp --config [flags] - configures your Test++ settings\n"
        "\ttestpp --cxx [compiler_flags] - configures your current Test++ compiler flags."
                            "\n\t\tType them in as if you were passing them directly to the compiler\n\n"
        "\ttestpp --link [libs] - configures your current Test++ libraries and frameworks to PRIVATELY link against\n"
        "\ttestpp --inspect [paths] - adds .cmake files to your current Test++ executable's CMakeLists\n"
        "\t - Add \"--g\" or \"--global\" to the beginning or the end to these commands to run this command globally\n\n"
        
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
}
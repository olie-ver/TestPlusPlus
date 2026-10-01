#include "../headers/Configure.hpp"

#include "../headers/Helpers.hpp"
#include "../headers/FileSystem.hpp"
#include "../headers/Metadata.hpp"
#include "../headers/PrintCommands.hpp"
#include "../headers/ResetCommands.hpp"

#include <iostream>
#include <sstream>
#include <string_view>

#define DEFAULT_FLAGS "default_flag.conf"

int main(int argc, char** argv) {
    std::filesystem::path last_exec_dir = testppCLI::GetLastExec();
    std::string last_exec_name{last_exec_dir.filename().string()};

    std::filesystem::path install_root = testppCLI::GetInstallRoot();
    std::filesystem::path var = install_root / "var";
    std::filesystem::path run = install_root / "run" / "testpp";

    //get the last executable and run it with the user's settings
    if (argc == 1) {
        #if defined(_WIN32) || defined(_WIN64)
            if (!std::filesystem::exists(last_exec_dir / "bin" / "Release" / "testpp_generated.exe")) {
        #else
            if (!std::filesystem::exists(last_exec_dir / "bin" / "testpp_generated")) {
        #endif
            std::cout << "No test executable has been made yet" << std::endl;
            return EXIT_SUCCESS;
        } 

        //Get the associated metadata, check if it needs to be compiled
        //If so, rebuild the CMakeLists and run it
        //Then run the run command
        testppCLI::Metadata meta = testppCLI::GetMetadata(argv[1]);
        if (meta.compile) {
            testppCLI::buildCMake(argv[1]);
            testppCLI::buildExec(argv[1]);
            meta.compile = false;
            meta.Serialize(last_exec_dir / "meta.data");
        }
        
        testppCLI::Config config = testppCLI::Config::Deserialize((last_exec_dir / "flags.conf"));
        std::stringstream cmd;
        cmd  << (last_exec_dir / last_exec_name) << ' ' << config;

        return system(cmd.str().c_str());
    }

    std::string_view first_arg{argv[1]};

    if (argc == 2) {
        // 2 ARG COMMANDS
        if (first_arg == "--help" || first_arg == "--h") {
            testppCLI::help();
        } else if (first_arg == "--diagnostics" || first_arg == "--d") {
            testppCLI::diagnostics();
        } else if (first_arg == "--version" || first_arg == "--v") {
            testppCLI::version();
        } else if (first_arg == "--list" || first_arg == "--l") {
            testppCLI::listExecs();
        } else if (first_arg == "--reset") {
            testppCLI::reset();
        } else if (first_arg == "--reset-flags") {
            testppCLI::resetFlags();
        } else if (first_arg == "--reset-cxx") {
            testppCLI::resetCxx();
        } else if (first_arg == "--reset-link") {
            testppCLI::resetLink();
        } else if (first_arg == "--default") {
            testppCLI::defaultReset();
        } else if (first_arg == "--default-flags") {
            testppCLI::defaultFlags();
        } else if (first_arg == "--default-cxx") {
            testppCLI::defaultCxx();
        } else if (first_arg == "--default-link") {
            testppCLI::defaultLink();
        } else if (first_arg == "--inspect") {
            testppCLI::inspect(argc, argv);
            return EXIT_SUCCESS;
        } else if (first_arg == "--delete") {
            testppCLI::deleteExec(argc, argv);
            return EXIT_SUCCESS;
        } else {

            //If the first arg is a flag instead of a name, print the usage and return exit failure
            if (testppCLI::IsFlag(first_arg)) {
                std::cerr << "Incorrect usage of flag: " << first_arg << "\n\n";
                testppCLI::help();

                return EXIT_FAILURE;
            }

            //If it's a flag => don't allow
            //If it's a file or a folder => add to the metadata
            //   build CMake and run
            //If it's a name => rerun the executable

            if (testppCLI::IsExec(first_arg)) {
                #if defined(_WIN32) || defined(_WIN64)
                    if (!std::filesystem::exists(run / first_arg / "bin" / "Release" / "testpp_generated.exe")) {
                #else
                    if (!std::filesystem::exists(run / first_arg / "bin" / "testpp_generated")) {
                #endif
                    std::cerr << "No test executable exists inside the directory: " << (run / first_arg) 
                        << ".\nPlease create one by using \"testpp [name] [files] [args]\".\n"
                        << "Where [name] is an optional parameter";
                    return EXIT_FAILURE;
                }

                //If there is an executable, then set it to be the one that will be run
                last_exec_name = first_arg;
            } else {
                if (std::filesystem::is_regular_file(first_arg) || std::filesystem::is_directory(first_arg)) {
                    std::vector<std::filesystem::path> files;
                    std::vector<std::string> args;
                    testppCLI::getFilesAndArgs(1, argc, argv, files, args);

                    testppCLI::Metadata meta = testppCLI::Metadata::Deserialize(last_exec_dir / "meta.data");
                    meta.compile = false;
                    meta.files = testppCLI::implode(files, " ");
                    meta.Serialize(last_exec_dir / "meta.data");

                    testppCLI::buildCMake(last_exec_name);
                    testppCLI::buildExec(last_exec_name);
                }
            }

            testppCLI::Config config = testppCLI::Config::Deserialize((run /last_exec_name / "flags.conf"));

            std::stringstream cmd;
            #if defined(_WIN32) || defined(_WIN64)
                cmd << '\"' << (run / last_exec_name / "bin" / "Release" /"testpp_generated.exe") << "\" " << config;
            #else
                cmd << '\"' << (run / last_exec_name / "bin" / "testpp_generated") << "\" " << config;
            #endif

            return system(cmd.str().c_str());
        }

        return EXIT_SUCCESS;
    }

    if (argc >= 2) {
        // GLOBAL COMMANDS
        if (first_arg == "--g" || first_arg == "--global") {
            if (argc < 3) {
                std::cerr << "Must provide a command flag after the global flag\n";
                abort();
            }

            std::string_view second{argv[2]};

            if (second == "--config") {
                testppCLI::globalConfigureFlags(3, argc, argv); //testpp --g --config [arg at index 3]
            } else if (second == "--cxx") {
                testppCLI::globalConfigureCXX(3, argc, argv);
            } else if (second == "--link") {
                testppCLI::globalConfigureLink(3, argc, argv);
            } else if (second == "--reset") {
                testppCLI::globalReset();
            } else if (second == "--reset-flags") {
                testppCLI::globalResetFlags();
            } else if (second == "--reset-cxx") {
                testppCLI::globalResetCxx();
            } else if (second == "--reset-link") {
                testppCLI::globalResetLink();
            } else if (second == "--default") {
                testppCLI::globalDefaultReset();
            } else if (second == "--default-flags") {
                testppCLI::globalDefaultFlags();
            } else if (second == "--default-cxx") {
                testppCLI::globalDefaultCxx();
            } else if (second == "--default-link") {
                testppCLI::globalDefaultLink();
            }

            return EXIT_SUCCESS;
        } else {
            std::string_view last{argv[argc - 1]};
            if (last == "--g" || last == "--global") {
                if (first_arg == "--config") {
                    //Needs a start and an end position
                    testppCLI::globalConfigureFlags(2, argc - 1, argv); //testpp --config [arg at index 2] 
                } else if (first_arg == "--cxx") {
                    testppCLI::globalConfigureCXX(2, argc - 1, argv);
                } else if (first_arg == "--link") {
                    testppCLI::globalConfigureLink(2, argc - 1, argv);
                } else if (first_arg == "--reset") {
                    testppCLI::globalReset();
                } else if (first_arg == "--reset-flags") {
                    testppCLI::globalResetFlags();
                } else if (first_arg == "--reset-cxx") {
                    testppCLI::globalResetCxx();
                } else if (first_arg == "--reset-link") {
                    testppCLI::globalResetLink();
                } else if (first_arg == "--default") {
                    testppCLI::globalDefaultReset();
                } else if (first_arg == "--default-flags") {
                    testppCLI::globalDefaultFlags();
                } else if (first_arg == "--default-cxx") {
                    testppCLI::globalDefaultCxx();
                } else if (first_arg == "--default-link") {
                    testppCLI::globalDefaultLink();
                }

                return EXIT_SUCCESS;
            }
        }

        // 3 ARG COMMANDS
        if (first_arg == "--set-exec" || first_arg == "--set") {
            testppCLI::setExec(argc, argv);
            return EXIT_SUCCESS;
        } else if (first_arg == "--new") {
            testppCLI::createExec(argc, argv);
            return EXIT_SUCCESS;
        } else if (first_arg == "--inspect") {
            testppCLI::inspect(argc, argv);
            return EXIT_SUCCESS;
        } else if (first_arg == "--delete") {
            testppCLI::deleteExec(argc, argv);
            return EXIT_SUCCESS;
        }
        
        // 3+ ARG COMMANDS
        if (first_arg == "--config") {
            testppCLI::configureFlags(argc, argv);
            return EXIT_SUCCESS;
        } else if (first_arg == "--cxx") {
            testppCLI::configureCXX(argc, argv);
            return EXIT_SUCCESS;
        } else if (first_arg == "--link") {
            testppCLI::configureLink(argc, argv);
            return EXIT_SUCCESS;
        } else if (first_arg == "--rename") {
            testppCLI::rename(argc, argv);
            return EXIT_SUCCESS;
        }

        int start = 1; //By default, the first argument is either a file or a run flag, eg: testpp [files and args]
        if (testppCLI::IsExec(first_arg)) {
            start = 2; //If the first arg is a name, then the structure is: testpp [name] [files and args]
            last_exec_dir = (run / first_arg).string();
            last_exec_name = last_exec_dir.filename().string();
        }

        //Now gather the files and arguments
        std::vector<std::filesystem::path> files;
        std::vector<std::string> args;
        testppCLI::getFilesAndArgs(start, argc, argv, files, args);

        std::string argStr{testppCLI::implode(args, " ")};
        argStr.push_back(' ');

        std::cout << "Getting metadata from: " << (last_exec_dir / "meta.data") << '\n';
        testppCLI::Metadata metadata = testppCLI::Metadata::Deserialize(last_exec_dir / "meta.data");
        if (files.size() == 0) {
            if (metadata.compile) {
                metadata.compile = false;
                metadata.Serialize(last_exec_dir / "meta.data");

                testppCLI::buildCMake(last_exec_name);
                testppCLI::buildExec(last_exec_name);
            }
        } else {
            metadata.compile = false;
            metadata.files = testppCLI::implode(files, " ");
            metadata.Serialize(last_exec_dir / "meta.data");
            testppCLI::buildCMake(last_exec_name);
            testppCLI::buildExec(last_exec_name);
        }

        testppCLI::Config config = testppCLI::Config::Deserialize(last_exec_dir / "flags.conf");
        std::stringstream stream;
        #if defined(_WIN32) || defined(_WIN64)
            stream << '\"' << (last_exec_dir / "bin" / "Release" / "testpp_generated.exe") << "\" " << argStr << config; //Needs the user's arguments in front of their config
        #else 
            stream << '\"' << (last_exec_dir / "bin" / "testpp_generated") << "\" " << argStr << config; //Needs the user's arguments in front of their config
        #endif

        std::cout << "Run command: " << stream.str() << '\n';

        return std::system(stream.str().c_str());
    }

}
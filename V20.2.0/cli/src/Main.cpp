#include "../headers/Configure.hpp"

#include "../headers/Helpers.hpp"
#include "../headers/FileSystem.hpp"
#include "../headers/Metadata.hpp"
#include "../headers/PrintCommands.hpp"
#include "../headers/ResetCommands.hpp"

#include <iostream>
#include <sstream>

#define DEFAULT_FLAGS "default_flag.conf"

//Forgot to add in --delete and --delete [name]

int main(int argc, char** argv) {
    std::filesystem::path last_exec_dir = testppCLI::GetLastExec();
    std::string last_exec_name{last_exec_dir.filename()};

    std::cout << "last_exec_dir: " << last_exec_dir << '\n';
    std::cout << "last_exec_name: " << last_exec_name << '\n';

    std::filesystem::path install_root = testppCLI::GetInstallRoot();
    std::filesystem::path var = install_root / "var";
    std::filesystem::path run = install_root / "run" / "testpp";

    //get the last executable and run it with the user's settings
    if (argc == 1) {
        std::cout << "argc == 1 => Last exec dir: ";
        std::cout << last_exec_dir << std::endl;

        if (!std::filesystem::exists(last_exec_dir / last_exec_name)) {
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

        std::cout << "Command: ";
        std::cout << cmd.str().c_str() << std::endl;

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
            //THIS PATH IS REALLY REALLY BUGGY FOR SOME REASON

            //If the first arg is a flag instead of a name, print the usage and return exit failure
            if (testppCLI::IsFlag(first_arg)) {
                std::cerr << "Incorrect usage of flag: " << first_arg << "\n\n";
                testppCLI::help();

                return EXIT_FAILURE;
            }

            //If first arg is an executable name, check if it exists first
            if (testppCLI::IsExec(first_arg)) {
                std::cout << "IS EXEC\n";
                if (!std::filesystem::exists(run / first_arg / first_arg)) {
                    std::cerr << "No test executable exists inside the directory: " << (run / first_arg) 
                        << ".\nPlease create one by using \"testpp [name] [files] [args]\".\n"
                        << "Where [name] is an optional parameter";
                    return EXIT_FAILURE;
                }

                //If it is an executable, then set it to be the one that will be run
                last_exec_name = first_arg;
            } else {
                std::cout << "IS NOT EXEC\n";
                std::cout << "Deserializing at: " << (last_exec_dir / "meta.data") << '\n';
                //otherwise take the file, add it to the Metadata, build the CMake and the executable
                testppCLI::Metadata meta = testppCLI::Metadata::Deserialize(last_exec_dir / "meta.data");
                meta.compile = false;
                meta.files = first_arg;
                meta.Serialize(last_exec_dir / "meta.data");

                testppCLI::buildCMake(last_exec_name);
                testppCLI::buildExec(last_exec_name);
            }

            testppCLI::Config config = testppCLI::Config::Deserialize((run /last_exec_name / "flags.conf"));

            std::stringstream cmd;
            cmd << '\"' << (run / last_exec_name / "bin" / "testpp_generated") << "\" " << config;

            std::cout << "Command (2 args):\n";
            std::cout << cmd.str().c_str() << std::endl;

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
                testppCLI::globalConfigureFlags(argc, argv);
            } else if (second == "--cxx") {
                testppCLI::globalConfigureCXX(argc, argv);
            } else if (second == "--link") {
                testppCLI::globalConfigureLink(argc, argv);
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
                    testppCLI::globalConfigureFlags(argc, argv);
                } else if (first_arg == "--cxx") {
                    testppCLI::globalConfigureCXX(argc, argv);
                } else if (first_arg == "--link") {
                    testppCLI::globalConfigureLink(argc, argv);
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
            std::cout << "CREATING NEW EXEC\n";
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

        //Check if the second argument is a name
        //If so, run that executable, otherwise run the default one
        std::string_view second{argv[2]};
        int start = 2;
        if (testppCLI::IsExec(second)) {
            //If the second argument is a name, change the path to be the folder containing the executable with that name
            last_exec_dir = (run / second).string();
            start += 1;
        }

        //If there are no files, but the configuration changed, then reconstruct the cmake and recompile the executable
        //If there are files, reconstruct the cmake, change the metadata and recompile the executable
        std::vector<std::filesystem::path> files;
        std::vector<std::string> args;
        testppCLI::getFilesAndArgs(start, argc, argv, files, args);

        testppCLI::Metadata execMeta = testppCLI::Metadata::Deserialize(last_exec_dir / "meta.data");
        if (files.size() == 0 && execMeta.compile) {
            execMeta.compile = false;
            execMeta.Serialize(last_exec_dir / "meta.data");

            testppCLI::buildCMake(second);
            testppCLI::buildExec(second);
        } else if (files.size() != 0) {
            execMeta.compile = false;
            execMeta.files = testppCLI::implode(files, " ");
            execMeta.Serialize(last_exec_dir / "meta.data");

            testppCLI::buildCMake(second);
            testppCLI::buildExec(second);
        }

        //Now build the run command and run it
        testppCLI::Config config = testppCLI::Config::Deserialize(last_exec_dir / "flags.conf");
        std::stringstream stream;
        stream << '\"' << (last_exec_dir / second) << '\"' << config; //Needs the user's arguments in front of their config

        std::cout << stream.str() << '\n';

        return std::system(stream.str().c_str());
    }

}
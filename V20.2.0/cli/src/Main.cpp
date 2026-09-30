#include "../headers/Configure.hpp"

#include "../headers/Helpers.hpp"
#include "../headers/FileSystem.hpp"
#include "../headers/Metadata.hpp"
#include "../headers/PrintCommands.hpp"
#include "../headers/ResetCommands.hpp"

#include <iostream>
#include <sstream>

#define DEFAULT_FLAGS "default_flag.conf"

int main(int argc, char** argv) {
    std::filesystem::path last_exec_dir = testppCLI::GetLastExec();
    std::string last_exec_name{last_exec_dir.parent_path().filename()};
    if (last_exec_dir.empty()) {
        std::cout << "No test executable has been made yet" << std::endl;
        return EXIT_SUCCESS;
    } 

    std::cout << last_exec_dir << std::endl;

    std::filesystem::path install_root = testppCLI::GetInstallRoot();
    std::filesystem::path var = install_root / "var";
    std::filesystem::path run = install_root / "run";

    if (argc == 1) {
        //get the last executable and run it with the user's settings

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
        cmd << '\"' << (last_exec_dir / last_exec_name) << "\" " << config;

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
        } else {
            //first_arg is an executable name
            if (!std::filesystem::exists(run / first_arg / first_arg)) {
                std::cerr << "No test executable exists inside the directory: " << (run / first_arg) 
                    << ". Please create one by using \"testpp [name] [files] [args]\".\n";
                return EXIT_FAILURE;
            }

            testppCLI::Config config = testppCLI::Config::Deserialize((run / first_arg / "flags.conf"));

            std::stringstream cmd;
            cmd << '\"' << (run / first_arg / first_arg) << "\" " << config;

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
            }

            return EXIT_SUCCESS;
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
        stream << '\"' << (last_exec_dir / second) << '\"' << config;

        std::cout << stream.str() << '\n';

        return std::system(stream.str().c_str());
    }


//     std::filesystem::path installRoot = tppCLI::GetInstallPrefix();

//     std::filesystem::path run = installRoot / "run" / "testpp";
//     std::filesystem::path var = installRoot / "var";
//     #if defined(_WIN32) || defined(_WIN64)
//         std::filesystem::path user_exec = run / "bin" / "Release" / "testpp_generated.exe";
//     #else
//         std::filesystem::path user_exec = run / "bin" / "testpp_generated";
//     #endif
//     std::filesystem::path user_conf = run / "config_flags.conf";
//     std::filesystem::path user_cxx = run / "config_cxx.conf";
//     std::filesystem::path cmake_template = var / "CMakeLists.txt.in";

//     std::filesystem::remove(run / "CMakeCache.txt");

//     if (!std::filesystem::exists(user_conf)) {
//         //If there isn't a configuration file, copy over the default 
//         std::filesystem::copy_file(var / DEFAULT_FLAGS, user_conf);
//     }

//     if (!std::filesystem::exists(user_cxx)) {
//         //If there isn't a cxx file, copy over the default 
//         std::filesystem::copy_file(var / "default_cxx.conf", user_cxx);
//     }

//     std::ifstream readConfig(user_conf);
//     std::stringstream configSettings;
//     configSettings << readConfig.rdbuf();

//     const tppCLI::CXX& cxx = tppCLI::getCXX(user_cxx);

//     if (argc == 1) {
//         if (!std::filesystem::exists(user_exec)) {
//             std::cout << "No tests to run" << std::endl;
//             return EXIT_SUCCESS;
//         }

//         std::string cmd = '\"' + user_exec.string() + '\"' + " " + configSettings.str();

//         return std::system(cmd.c_str());
//     }

//     if (argc == 2) {
//         std::string_view first{argv[1]};

//         if (std::find(tppCLI::flags.begin(), tppCLI::flags.end(), first) == tppCLI::flags.end()) {
//             tppCLI::usage(first);
//             return EXIT_FAILURE;
//         }

//         if (first == "--help" || first == "--h") {
//             tppCLI::help();
//         } else if (first == "--diagnostics" || first == "--d") {
//             tppCLI::diagnostics();
//         } else if (first == "--version" || first == "--v") {
//             tppCLI::version();
//         } 
        
//         if (std::find(tppCLI::resetFlags.begin(), tppCLI::resetFlags.end(), first) == tppCLI::resetFlags.end()) {
//             tppCLI::usage(first);
//             return EXIT_FAILURE;
//         }
        
//         if (first == "--reset") {
//             tppCLI::reset();
//         } else if (first == "--reset-flags") {
//             tppCLI::reset_flags();
//         } else if (first == "--reset-cxx") {
//             tppCLI::reset_cxx();
//         }

//         return EXIT_SUCCESS;
//     }

//     if (argc >= 2) {
//         std::string first_arg{argv[1]};

//         // if (first_arg == "--reset") {
//         //     std::filesystem::copy_file(var / DEFAULT_FLAGS, user_conf, 
//         //         std::filesystem::copy_options::overwrite_existing);

//         //     std::filesystem::copy_file(var / "default_cxx.conf", user_cxx,
//         //         std::filesystem::copy_options::overwrite_existing);
    
//         //     return EXIT_SUCCESS;
//         // }

//         // if (first_arg == "--reset-flags") {
//         //     std::filesystem::copy_file(var / DEFAULT_FLAGS, user_conf, 
//         //         std::filesystem::copy_options::overwrite_existing);
//         //     return EXIT_SUCCESS;
//         // }

//         // if (first_arg == "--reset-cxx") {
//         //     std::filesystem::copy_file(var / "default_cxx.conf", user_cxx,
//         //         std::filesystem::copy_options::overwrite_existing);
    
//         //     return EXIT_SUCCESS;
//         // }

//         if (first_arg == "config") {
//             //config the file then return
//             tppCLI::CreateConfig(user_conf, argc, argv);
//             return EXIT_SUCCESS;
//         }

//         if (first_arg == "cxx_flags") {
//             //write to the cxx flag file then return
//             std::ofstream cxx_stream(user_cxx.c_str(), std::ios::trunc);
//             std::string flags = "Flags: ";
//             std::string std = "Standard: ";
//             std::string libs = "Libraries: ";
//             for (int i = 2; i < argc; i++) {
//                 if (std::string_view(argv[i]).find("-std=c++") != std::string_view::npos) {
//                     std += argv[i];
//                 } else if (std::string_view(argv[i]).find("-lib=") != std::string_view::npos) {
//                     libs += argv[i];
//                 } else {
//                     flags += argv[i];
//                     flags += " ";
//                 }
//             }
//             cxx_stream << flags << '\n';
//             cxx_stream << std << '\n';
//             cxx_stream << libs;
//             return EXIT_SUCCESS;
//         }
//     }

//     //gather files and args
//     std::vector<std::string> args{" "};

//     std::vector<std::filesystem::path> files;

//     tppHelpers::getFilesAndArgs(argc, argv, args, files);

//     //if no files were specifed, rerun the generated executable
//     //  under any flags that were given
//     if (files.size() == 0) {
//         if (!std::filesystem::exists(user_exec)) {
//             std::cout << "No tests to run" << std::endl;
//             return EXIT_SUCCESS;
//         }

//         std::stringstream argStream;

//         for (size_t i = 0; i < args.size(); i++) {
//             argStream << args[i] << " ";
//         }

//         std::string run_command = '\"' + user_exec.string() + '\"' + " " + configSettings.str() + argStream.str();
//         return std::system(run_command.c_str());
//     }

//     tppHelpers::generateCMake(installRoot, run / "CMakeLists.txt", cmake_template, files, cxx);

//     if (!tppHelpers::configureAndBuild(run)) {
//         return EXIT_FAILURE;
//     }

//     std::stringstream argStream;

//     for (size_t i = 0; i < args.size(); i++) {
//         argStream << args[i] << " ";
//     }

//     //Run command is "user_exec" configSettings arguments
//     // arguments override any configSettings so it's all good to just add them in front
//     std::string run_command = '\"' + user_exec.string() + '\"' + " " + configSettings.str() + argStream.str();

//     return std::system(run_command.c_str());
}
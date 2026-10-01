#include "../../headers/Configure.hpp"
#include "../../headers/FileSystem.hpp"

#include <fstream>
#include <iostream>
#include <string_view>

namespace testppCLI {
    //Probably not implemented correctly
    void setExec(int argc, char** argv) {
        if (argc != 3) {
            std::cerr << "Incorrect number of arguments: " << argc << ". Usage: testpp --set-exec [name]" << std::endl;
            abort();
        }

        std::string_view second_arg{argv[2]};

        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};

        if (!std::filesystem::exists(run / second_arg)) {
            std::cerr << "Executable does not exist at path: " << (run / second_arg) << std::endl;
            abort();
        }

        std::filesystem::path defaultPathConfig{installRoot / "var" / "last_exec.conf"};

        std::ofstream ofstream(defaultPathConfig, std::ios::trunc);
        std::string path{second_arg};
        ofstream.write(path.data(), path.length());
        ofstream.close();

        std::cout << "Set active executable to: \"" << second_arg << "\"\n";
    }

    void createExec(int argc, char** argv) {
        if (argc != 3) {
            std::cerr << "Incorrect number of arguments: " << argc << ". Usage: testpp --new [name]" << std::endl;
            abort();
        }

        std::string_view second_arg{argv[2]};

        if (second_arg.find("../") != std::string_view::npos) {
            std::cerr << "Filename contained \"../\". Please reenter a new name without \"../\"\n";
            abort();
        }

        if (IsFlag(second_arg)) {
            std::cerr << "Filename started with a reserved string.\n";
            abort();
        }

        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path var{installRoot / "var"};
        std::filesystem::path run{installRoot / "run" / "testpp"};
        std::filesystem::path newExecDir{run / second_arg};

        if (std::filesystem::exists(newExecDir)) {
            std::cerr << "Executable " << newExecDir.filename() << " already exists.";
            abort();
        }
        
        std::filesystem::create_directory(newExecDir);
        std::filesystem::copy_file(var / "default_meta.data", newExecDir / "meta.data");
        std::filesystem::copy_file(run / "global_flags.conf", newExecDir / "flags.conf");
        std::filesystem::copy_file(run / "global_cxx.conf", newExecDir / "cxx.conf");

        std::cout << "Created new executable: " << newExecDir.filename() << '\n';

        std::vector<const char*> newArgv{"testpp", "--set-exec", argv[2], nullptr};

        //set the path to the new executable path, even though it's not yet constructed
        setExec(static_cast<int>(newArgv.size() - 1),  const_cast<char**>(newArgv.data()));
    }

    void deleteExec(int argc, char** argv) {
        std::string name;

        if (argc == 2) {
            name = GetLastExec().filename().string();
        } else {
            if (argc != 3) {
                std::cerr << "Incorrect usage. Expected \"testpp --delete [name]\" where [name] is optional\n";
                abort();
            }

            name = argv[2];
        }

        std::cout << "deleteExec() name: " << name << '\n';

        if (name.find("../") != std::string::npos) {
            std::cerr << "Executable name contained \"../\". Please do not try to delete random files and folders.\n";
            abort();
        }

        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};
        if (!std::filesystem::exists(run / name)) {
            std::cerr << "No executable with the name: " << name << '\n';
            abort();
        }

        std::filesystem::remove_all(run / name);

        std::cout << "Deleted executable \"" << name << "\"\n";

        //Not switching the default executable properly, needs a stronger test other than "no more directories"

        //If we deleted the active executable
        if (name == GetLastExec().filename().string()) {
            //And if there is no default executable
            if (!std::filesystem::exists(installRoot / "run" / "testpp" / "testpp_default")) {
                std::vector<const char*> newArgv{"testpp", "--new", "testpp_default", nullptr};

                //Create testpp_default as the new active executable
                createExec(static_cast<int>(newArgv.size() - 1),  const_cast<char**>(newArgv.data()));
            } else {
                std::ofstream ofstream(installRoot / "var" / "last_exec.conf", std::ios::trunc);
                ofstream.write("testpp_default", 14);
                ofstream.close();

                std::cout << "Set active executable: \"testpp_default\"\n";
            }
        }
    }

    bool IsExec(std::string_view name) {
        std::filesystem::path execs{GetInstallRoot() / "run" / "testpp"};

        for (const auto& iter : std::filesystem::directory_iterator(execs)) {
            if (iter.path().filename() == name) {
                return true;
            }
        }

        return false;
    }

    bool IsFlag(std::string_view name) {
        for (size_t i = 0; i < commands.size(); i++) {
            if (name.starts_with(commands[i])) {
                return true;
            }
        }

        return false;
    }
}
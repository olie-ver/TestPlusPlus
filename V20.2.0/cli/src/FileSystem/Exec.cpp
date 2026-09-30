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
        setExec(newArgv.size() - 1,  const_cast<char**>(newArgv.data()));
    }

    void deleteExec(std::string_view name) {
        if (name.find("../") == std::string_view::npos) {
            std::cerr << "Filepath contained \"../\". Please do not try to delete random files and folders.\n";
            abort();
        }

        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};
        if (!std::filesystem::exists(run / name)) {
            std::cerr << "No executable with the name: " << name << '\n';
        } else if (!std::filesystem::is_directory(run / name)) {
            std::cerr << "The provided name is not an executable directory." 
                "Please enter the name of the executable you want to delete instead of its path\n";
            abort();
        } else {
            std::filesystem::remove(run / name);
        }
    }

    bool IsExec(std::string_view name) {
        std::cout << "IsExec() name: " << name << '\n';
        for (size_t i = 0; i < commands.size(); i++) {
            if (name.starts_with(commands[i])) {
                return false;
            }
        }
        std::filesystem::path path(GetInstallRoot() / "run" / "testpp" / name);
        return std::filesystem::exists(path / name) && std::filesystem::is_directory(path);
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
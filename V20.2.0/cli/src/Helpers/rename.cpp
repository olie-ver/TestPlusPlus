#include "../../headers/Helpers.hpp"

#include "../../headers/FileSystem.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

namespace testppCLI {
    void rename(int argc, char** argv) {
        if (argc != 4) {
            std::cerr << "rename(): invalid usage. Expected usage: \"testpp --rename [name] [rename]\"\n";
            abort();
        }

        std::string_view name{argv[3]};
        if (name.find("../") != std::string_view::npos) {
            std::cerr << "Name contains \"../\". Please provide a new name that does not contain that.\n";
            abort();
        }

        std::filesystem::path renameFrom{GetInstallRoot() / "run" / "testpp" / argv[2]};
        std::filesystem::path renameTo(GetInstallRoot() / "run" / "testpp" / argv[3]);
        std::filesystem::rename(renameFrom, renameTo);

        //read in the last executable
        std::fstream fstream{GetInstallRoot() / "var" / "last_exec.conf", std::ios::trunc};
        std::string lastExec;
        getline(fstream, lastExec);
        if (lastExec == renameFrom) {
            fstream << renameTo;
        }
    }
}
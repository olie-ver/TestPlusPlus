#include "../../headers/PrintCommands.hpp"
#include "../../headers/FileSystem.hpp"

#include <filesystem>
#include <iostream>

namespace testppCLI {
    void listExecs() {
        std::filesystem::path installRoot{GetInstallRoot()};
        std::filesystem::path run{installRoot / "run" / "testpp"};

        std::cout << "Executable names:\n";

        size_t numExecutables{0};
        for (const auto& iter : std::filesystem::directory_iterator(run)) {
            if (std::filesystem::is_directory(iter.path())) {
                std::cout << iter.path().parent_path().filename() << '\n';
                numExecutables++;
            }
        }

        if (!numExecutables) {
            std::cout << "No executables\n";
        }
        
        std::cout << std::flush;
    }
}
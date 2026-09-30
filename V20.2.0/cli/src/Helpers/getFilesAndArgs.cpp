#include "../../headers/Helpers.hpp"

namespace testppCLI {
    void getFilesAndArgs(int start, int argc, char** argv, std::vector<std::filesystem::path>& files, std::vector<std::string>& args) {
        for (; start < argc; start++) {
            std::filesystem::path path{argv[start]};

            if (std::filesystem::is_regular_file(path)) {
                if (path.extension() == ".cpp" || path.extension() == ".cc" || path.extension() == ".c++") {
                    files.push_back(path);
                } 
            } else if (std::filesystem::is_directory(path)) {
                for (const auto& entry : std::filesystem::recursive_directory_iterator(path)) {
                    if (entry.path().extension() == ".cpp" || entry.path().extension() == ".cc" || entry.path().extension() == ".c++") {
                        files.push_back(entry.path());
                    }
                }
            } else {
                args.push_back(argv[start]);
            }
        }
    }
}
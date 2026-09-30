#include "../../headers/Configure.hpp"

#include <fstream>

namespace testppCLI {
    void Config::Serialize(const std::filesystem::path& path) {
        std::ofstream file(path, std::ios::binary | std::ios::trunc);

        file.write(reinterpret_cast<const char*>(this), sizeof(*this));
    }

    Config Config::Deserialize(const std::filesystem::path& path) {
        Config conf;
        std::ifstream file(path, std::ios::binary);

        file.read(reinterpret_cast<char*>(&conf), sizeof(conf));

        return conf;
    }

    void CXX::Serialize(const std::filesystem::path& path) {
        //open the file and clear all content
        std::ofstream file(path, std::ios::binary | std::ios::trunc);
        file.write(reinterpret_cast<const char*>(this), sizeof(*this));
    }

    CXX CXX::Deserialize(const std::filesystem::path& path) {
        CXX cxx;

        std::ifstream file(path, std::ios::binary);

        file.read(reinterpret_cast<char*>(&cxx), sizeof(cxx));

        return cxx;
    }
}
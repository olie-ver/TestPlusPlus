#include "../../headers/Metadata.hpp"
#include "../../headers/Helpers.hpp"

#include <fstream>

namespace testppCLI {
    std::ostream& operator<< (std::ostream& stream, const Metadata& meta) {
        stream << "Recompile: " << meta.compile << '\n';
        stream << "Source files: \n";
        const std::vector<std::string>& files = split(meta.files, " ");
        for (size_t i = 0; i < files.size(); i++) {
            stream << '\t' << files[i] << '\n';
        }

        return stream;
    }

    bool operator== (const Metadata& lhs, const Metadata& rhs) {
        return lhs.compile == rhs.compile && lhs.files == rhs.files;
    }

    void Metadata::Serialize(const std::filesystem::path& path) {
        std::ofstream file(path, std::ios::binary | std::ios::trunc);

        file.write(reinterpret_cast<const char*>(&compile), sizeof(compile));

        uint64_t size = files.size();
        file.write(reinterpret_cast<const char*>(&size), sizeof(size));

        file.write(files.data(), size);
    }

    Metadata Metadata::Deserialize(const std::filesystem::path& path) {
        Metadata data;

        std::ifstream file(path, std::ios::binary);

        file.read(reinterpret_cast<char*>(&data.compile), sizeof(data.compile));

        uint64_t size;
        file.read(reinterpret_cast<char*>(&size), sizeof(size));

        data.files.resize(size);
        file.read(data.files.data(), size);

        return data;
    }
}
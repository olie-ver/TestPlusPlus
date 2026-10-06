#include "../../headers/Helpers.hpp"

#include <string>

namespace testppCLI {
    std::string replace(const std::string& s, const std::string& delimiter, const std::string& replace) {
        size_t pos = 0;
        std::string token = s;
        while ((pos = token.find(delimiter)) != std::string::npos) {
            token.replace(pos, delimiter.length(), replace);
        }

        return token;
    }
}
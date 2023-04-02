#pragma once

#include <algorithm>
#include <string>

namespace UserInterface::Private::Util {

    // Converts std::string to lowercase
    std::string ToLower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
}

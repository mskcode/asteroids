#pragma once

#include <string>
#include <string_view>

namespace common::file {

auto read_file(std::string_view path) -> std::string;

constexpr auto file_name(const char* path) -> const char* {
    const char* file = path;
    while (*path != 0) {
        if (*path++ == '/') {
            file = path;
        }
    }
    return file;
}

} // namespace common::file

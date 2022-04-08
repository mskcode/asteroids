#ifndef COMMON_FILEUTILS_H
#define COMMON_FILEUTILS_H

#include <string>
#include <string_view>

namespace common::file {

auto read_file(std::string_view path) -> std::string;

} // namespace common::file

#endif //  COMMON_FILEUTILS_H

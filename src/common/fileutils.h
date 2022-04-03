#ifndef COMMON_UTILS_FILEUTILS_H
#define COMMON_UTILS_FILEUTILS_H

#include <string>
#include <string_view>

namespace fileutils {

auto read_file(std::string_view path) -> std::string;

} // namespace fileutils

#endif // COMMON_UTILS_FILEUTILS_H

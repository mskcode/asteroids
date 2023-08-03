#pragma once

#include <string>
#include <string_view>

namespace common::file {

auto read_file(std::string_view path) -> std::string;

} // namespace common::file

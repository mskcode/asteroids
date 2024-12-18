#pragma once

#include <cerrno>
#include <cstring>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace common::str {

template <typename... Args>
auto format(const std::string& format, Args... args) -> std::string {
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args...) + 1; // extra space for '\0'
    if (size_s <= 0) {
        return "Formatting string failed (errno " + std::string(std::strerror(errno)) + ")";
    }

    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return {buf.get(), buf.get() + size - 1}; // exclude the trailing '\0'
}

} // namespace common::str

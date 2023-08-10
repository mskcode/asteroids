#include "dump.h"
#include <cctype>
#include <fmt/core.h>
#include <iostream>
#include <string>

auto common::dump_memory(const u8* const ptr, size_t size) -> void {
    std::cout << fmt::format("=== Object@{:p} | {} bytes ===", reinterpret_cast<const void*>(ptr), size) << '\n';
    u8 line_counter = 0;
    u8 char_counter = 0;
    std::string hex_line;
    std::string ascii_line;
    for (size_t i = 0; i < size; ++i) {
        u8 byte = ptr[i];

        if (char_counter == 8) {
            // add double space between 8 bytes
            hex_line += " ";
        }

        hex_line += fmt::format("{:02x} ", byte);
        ascii_line += std::isprint(byte) ? byte : '.';

        char_counter += 1;
        if (char_counter == 16 || i == size - 1) {
            std::cout << fmt::format("{:08x}  {:50} {:16}", line_counter * 16, hex_line, ascii_line) << '\n';

            line_counter += 1;
            char_counter = 0;
            hex_line = "";
            ascii_line = "";
        }
    }
}

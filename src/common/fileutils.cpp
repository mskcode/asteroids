#include "fileutils.h"
#include "debug.h"
#include <fstream>

using namespace fileutils;

auto fileutils::read_file(const std::string_view path) -> std::string {
    auto stream = std::ifstream(path.data());
    xassertf(stream.good(), "Could not open file %s", path.data());
    stream.exceptions(std::ios_base::badbit);

    constexpr auto read_size = std::size_t(4096);
    auto buf = std::string(read_size, '\0');

    auto out = std::string();
    while (stream.read(&buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}

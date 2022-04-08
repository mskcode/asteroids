#ifndef COMMON_DEBUG_H
#define COMMON_DEBUG_H

#include "strutils.h"
#include <cstdio>
#include <filesystem>
#include <stdexcept>

#ifdef NDEBUG
#define assert(ignore)
#define assertf(ignore)
#define dbgln(ignore)
#define dbgfln(ignore)
#else

// clang-format off

#define dbgln(fmt)       std::fprintf(stderr, "DEBUG: " fmt "\n")
#define dbgfln(fmt, ...) std::fprintf(stderr, "DEBUG: " fmt "\n", __VA_ARGS__)

// clang-format on

class AssertionError final : public std::runtime_error {
public:
    explicit AssertionError(const std::string& msg, const char* file = nullptr, unsigned int line = 0) :
        std::runtime_error("ASSERT FAILED " + std::string(file) + ":" + std::to_string(line) + " " + msg) {}
};

constexpr auto file_name(const char* path) -> const char* {
    const char* file = path;
    while (*path != 0) {
        if (*path++ == '/') {
            file = path;
        }
    }
    return file;
}

// clang-format off

#define xassert(exp, msg)       if (!(exp)) { throw AssertionError(msg, file_name(__FILE__), __LINE__); }
#define xassertf(exp, fmt, ...) if (!(exp)) { throw AssertionError(strutils::format(fmt, __VA_ARGS__), file_name(__FILE__), __LINE__); }

// clang-format on

#endif // NDEBUG

#endif //  COMMON_DEBUG_H

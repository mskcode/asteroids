#pragma once

#include <cstdio>

#ifdef NDEBUG
#define dbgln(ignore)
#define dbgfln(ignore, ...)

#define dprint(ignore)
#define dprint(ignore, ...)
#else

// clang-format off

#define dbgln(msg)       std::fprintf(stderr, "DEBUG: " msg "\n")
#define dbgfln(msg, ...) std::fprintf(stderr, "DEBUG: " msg "\n", __VA_ARGS__)

// clang-format on

#endif // NDEBUG

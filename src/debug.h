#ifndef ASTEROIDS_DEBUG_H
#define ASTEROIDS_DEBUG_H

#include <cstdio>

#ifdef DEBUG
#define dbgln(fmt) std::fprintf(stderr, "DEBUG: " fmt "\n")
#define dbgfln(fmt, ...) std::fprintf(stderr, "DEBUG: " fmt "\n", __VA_ARGS__)
#else
#define dbgln(x)
#define dbgfln(x)
#endif // DEBUG

#endif // ASTEROIDS_DEBUG_H

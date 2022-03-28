#ifndef ASTEROIDS_DEBUG_H
#define ASTEROIDS_DEBUG_H

#include <cstdio>

#ifdef DEBUG
#define debugln(fmt) std::fprintf(stderr, "DEBUG: " fmt "\n")
#define debugfln(fmt, ...) std::fprintf(stderr, "DEBUG: " fmt "\n", __VA_ARGS__)
#else
#define debugln(x)
#define debugfln(x)
#endif // DEBUG

#endif // ASTEROIDS_DEBUG_H

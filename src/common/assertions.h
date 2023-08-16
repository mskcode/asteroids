#pragma once

#include "fileutils.h"
#include "panic.h"
#include <fmt/core.h>
#include <iostream>
#include <stdexcept>

// ==========================================================================
// ASSERTION MACROS
// Compiled out in Release-mode
// ==========================================================================

#ifdef DEBUG

#define XASSERT_PRINT_LOCATION() std::cout << "ASSERT[" << common::file::file_name(__FILE__) << "@" << __LINE__ << "]: "
#define XASSERT_EXIT() PANIC_SILENT()

#define XASSERT(expr)                                                                                                  \
    if (!static_cast<bool>(expr)) {                                                                                    \
        XASSERT_PRINT_LOCATION();                                                                                      \
        std::cout << "Assertion " << #expr << " failed\n";                                                             \
        XASSERT_EXIT();                                                                                                \
    }

#define XASSERTM(expr, msg)                                                                                            \
    if (!static_cast<bool>(expr)) {                                                                                    \
        XASSERT_PRINT_LOCATION();                                                                                      \
        std::cout << msg << '\n';                                                                                      \
        XASSERT_EXIT();                                                                                                \
    }

#define XASSERTF(expr, msg, ...)                                                                                       \
    if (!static_cast<bool>(expr)) {                                                                                    \
        XASSERT_PRINT_LOCATION();                                                                                      \
        std::cout << fmt::format(msg, __VA_ARGS__) << '\n';                                                            \
        XASSERT_EXIT();                                                                                                \
    }

#else
#define XASSERT(exp)
#define XASSERTM(exp, msg)
#define XASSERTF(exp, msg, ...)
#endif

// ==========================================================================
// VERIFY MACROS
// Always in program regardless of release/debug mode
// ==========================================================================

#define VERIFY(expr)                                                                                                   \
    do {                                                                                                               \
        if (!static_cast<bool>(expr)) {                                                                                \
            PANIC("Verification failed: " #expr "\n");                                                                 \
        }                                                                                                              \
    } while (0)

#define VERIFY_NOT_IMPLEMENTED() PANIC("Not implemented")
#define VERIFY_NOT_REACHED() PANIC("Unreachable condition reached")

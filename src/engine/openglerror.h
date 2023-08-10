#pragma once

#include "../common/strutils.h"
#include <exception>
#include <fmt/core.h>
#include <stdexcept>
#include <string>

// clang-format off

#define throw_gl(msg) throw engine::opengl::OpenglException(msg, __FILE__, __LINE__)
#define throwf_gl(msg, ...) throw engine::opengl::OpenglException(fmt::format(msg, __VA_ARGS__), __FILE__, __LINE__)

// clang-format on

namespace engine::opengl {

class OpenglException : public std::runtime_error {
public:
    explicit OpenglException(const std::string& msg, const char* file = nullptr, unsigned int line = 0) :
        std::runtime_error(std::string(file) + ":" + std::to_string(line) + " " + msg) {}
};

inline void clear_errors() {
    GLenum status;
    while ((status = glGetError()) != GL_NO_ERROR) {}
}

inline void check_error(const char* statement, const char* filename, int line) {
    if (glGetError() == GL_NO_ERROR) {
        return;
    }

    GLenum status;
    std::string error_message;
    while ((status = glGetError()) != GL_NO_ERROR) {
        error_message += common::str::format("OpenGL error %08x, at %s:%i - for %s\n",
                                             status,
                                             filename,
                                             line,
                                             statement);
    }
    throw OpenglException(error_message, filename, line);
}

#ifdef NDEBUG
#define GL_CHECK(stmt) stmt
#else
#define GL_CHECK(stmt)                                                                                                 \
    do {                                                                                                               \
        engine::opengl::clear_errors();                                                                                \
        stmt;                                                                                                          \
        engine::opengl::check_error(#stmt, __FILE__, __LINE__);                                                        \
    } while (0)
#endif

} // namespace engine::opengl

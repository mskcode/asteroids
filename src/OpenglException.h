//
// Created by samuli on 3/29/22.
//

#ifndef OPENGL_OPENGLEXCEPTION_H
#define OPENGL_OPENGLEXCEPTION_H

#include <exception>
#include <string>
#include <stdexcept>

#define throw_gl(msg) throw OpenglException(msg, __FILE__, __LINE__)

namespace opengl {

class OpenglException : public std::runtime_error {
public:

    OpenglException(const std::string &msg, const char *file = nullptr, unsigned int line = 0) :
            std::runtime_error(std::string(file) + ":" + std::to_string(line) + " " + msg) {
    }

    ~OpenglException() throw() {}

private:
    char *file;
};

} // namespace

#endif // OPENGL_OPENGLEXCEPTION_H

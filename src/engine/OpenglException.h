#ifndef ENGINE_OPENGLEXCEPTION_H
#define ENGINE_OPENGLEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <string>

#define throw_gl(msg) throw OpenglException(msg, __FILE__, __LINE__)

namespace engine {

class OpenglException : public std::runtime_error {
public:
    explicit OpenglException(const std::string& msg, const char* file = nullptr, unsigned int line = 0) :
        std::runtime_error(std::string(file) + ":" + std::to_string(line) + " " + msg) {}
};

} // namespace engine

#endif // ENGINE_OPENGLEXCEPTION_H

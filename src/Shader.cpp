#include "Shader.h"

#include "OpenglException.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace opengl;

static std::string read_file(const char *path) {
    std::ifstream t(path);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

Shader Shader::load_string(GLenum shader_type, const char *str) {
    return Shader{shader_type, str};
}

Shader Shader::load_file(GLenum shader_type, const char *path) {
    auto source = read_file(path);
    return Shader{shader_type, source.c_str()};
}

Shader::Shader(GLenum shader_type, const char *shader_source) {
    shader_ = glCreateShader(shader_type);
    glShaderSource(shader_, 1, &shader_source, nullptr);
    glCompileShader(shader_);

    int success;
    glGetShaderiv(shader_, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader_, 512, nullptr, log);
        throw_gl("Compiling shader failed: " + std::string(log));
    }
}

Shader::~Shader() {
    // we are free to delete the shader once it has been linked into shader program
    glDeleteShader(shader_);
}

GLuint Shader::id() const {
    return shader_;
}

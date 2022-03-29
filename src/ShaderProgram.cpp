#include "ShaderProgram.h"

#include "OpenglException.h"
#include <cstdio>

using namespace opengl;

ShaderProgram::ShaderProgram() {
    program_ = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program_);
}

void ShaderProgram::attach_shader(Shader shader) {
    glAttachShader(program_, shader.id());
}

void ShaderProgram::attach_shaders(const std::vector<Shader> &shaders) {
    for (auto &shader: shaders) {
        attach_shader(shader);
    }
}

void ShaderProgram::link() {
    glLinkProgram(program_);

    int success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program_, 512, nullptr, log);
        throw_gl("Linking shaders failed: " + std::string(log));
    }
}

GLuint ShaderProgram::id() const {
    return program_;
}

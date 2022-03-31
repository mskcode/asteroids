#include "ShaderProgram.h"
#include "OpenglException.h"
#include "debug.h"
#include "strutils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace opengl;

static auto compile_shader(GLenum shader_type, const char* shader_source) -> GLuint {
    auto shader = glCreateShader(shader_type);
    dbgfln("Creating shader ID %d (shader_type=%d)", shader, shader_type);
    glShaderSource(shader, 1, &shader_source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        constexpr size_t buffer_size{512};
        char log[buffer_size];
        glGetShaderInfoLog(shader, buffer_size, nullptr, log);
        throw_gl("Compiling shader " + std::string(shader_source) + " failed: " + std::string(log));
    }

    return shader;
}

static auto read_file(const std::string& path) -> std::string {
    auto stream = std::ifstream(path.data());
    xassertf(stream.good(), "Could not open file %s", path.c_str());
    stream.exceptions(std::ios_base::badbit);

    constexpr auto read_size = std::size_t(4096);
    auto buf = std::string(read_size, '\0');

    auto out = std::string();
    while (stream.read(&buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());

    std::cout << "SOURCE:" << out << std::endl;
    return out;
}

ShaderProgram::ShaderProgram() {
    program_ = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    dbgfln("Destruct ShaderProgram ID %d", program_);
    glDeleteProgram(program_);
}

void ShaderProgram::load_shader_file(GLenum shader_type, const char* path) const {
    auto source = read_file(path);
    load_shader_string(shader_type, source.c_str());
}

void ShaderProgram::load_shader_string(GLenum shader_type, const char* str) const {
    auto shader = compile_shader(shader_type, str);
    dbgfln("Attaching and freeing shader ID %d", shader);
    glAttachShader(program_, shader);
    glDeleteShader(shader); // we can free the shader after attaching it
}

void ShaderProgram::link() const {
    glLinkProgram(program_);

    int success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        constexpr size_t buffer_size{512};
        char log[buffer_size];
        glGetProgramInfoLog(program_, buffer_size, nullptr, log);
        throw_gl("Linking shaders failed: " + std::string(log));
    }
}

auto ShaderProgram::id() const -> GLuint {
    return program_;
}

#include "ShaderProgram.h"
#include "../common/debug.h"
#include "OpenglException.h"
#include <string>

using namespace engine;

ShaderProgram::ShaderProgram(Shader vertex_shader, Shader fragment_shader) :
    fragment_shader_(std::move(fragment_shader)),
    vertex_shader_(std::move(vertex_shader)) {
    xassertf(fragment_shader_.is_fragment_shader(), "Shader ID %d not a fragment shader", fragment_shader_.id());
    xassertf(vertex_shader_.is_vertex_shader(), "Shader ID %d is not a vertex shader", vertex_shader_.id());

    program_ = glCreateProgram();
    dbgfln("Creating shader program ID %d", program_);
    glAttachShader(program_, vertex_shader_.id());
    glAttachShader(program_, fragment_shader_.id());

    dbgfln("Linking shader program ID %d", program_);
    glLinkProgram(program_);

    // we can free the shader GPU resources after attaching it
    // vertex_shader_.free_gpu_resources();
    // fragment_shader_.free_gpu_resources();

    int success;
    glGetProgramiv(program_, GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        constexpr size_t buffer_size{512};
        char log[buffer_size];
        glGetProgramInfoLog(program_, buffer_size, nullptr, log);
        throw_gl("Linking shaders failed: " + std::string(log));
    }
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) noexcept :
    program_(std::exchange(other.program_, 0)),
    fragment_shader_(std::move(other.fragment_shader_)),
    vertex_shader_(std::move(other.vertex_shader_)) {}

ShaderProgram::~ShaderProgram() {
    dbgfln("Deleting shader program ID %d", program_);
    free_gpu_resources();
}

auto ShaderProgram::operator=(ShaderProgram&& rhs) noexcept -> ShaderProgram& {
    if (this != &rhs) {
        free_gpu_resources();
        program_ = std::exchange(rhs.program_, 0);
        fragment_shader_ = std::move(rhs.fragment_shader_);
        vertex_shader_ = std::move(rhs.vertex_shader_);
    }
    return *this;
}

auto ShaderProgram::id() const -> GLuint {
    return program_;
}

auto ShaderProgram::vertex_shader() const -> const Shader& {
    return vertex_shader_;
}

auto ShaderProgram::fragment_shader() const -> const Shader& {
    return fragment_shader_;
}

auto ShaderProgram::query_attribute_location(const std::string_view& name) const -> GLint {
    auto location = glGetAttribLocation(program_, name.data());
    if (location < 0) {
        throw_gl("Attribute " + std::string(name) + " not found");
    }
    return location;
}

auto ShaderProgram::query_uniform_location(const std::string_view& name) const -> GLint {
    auto location = glGetUniformLocation(program_, name.data());
    if (location < 0) {
        throw_gl("Attribute " + std::string(name) + " not found");
    }
    return location;
}

void ShaderProgram::bind() const {
    glUseProgram(program_);
}

void ShaderProgram::customize(std::function<void(ShaderProgram&)> customizer) {
    glUseProgram(program_);
    customizer(*this);
    glUseProgram(0);
}

void ShaderProgram::free_gpu_resources() noexcept {
    if (program_ != 0) {
        dbgfln("Freeing ShaderProgram ID %d", program_);
        glDeleteProgram(program_);
        program_ = 0;
    }
}

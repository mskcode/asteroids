#include "Shader.h"
#include "../common/assertions.h"
#include "../common/debug.h"
#include "../common/fileutils.h"
#include "openglerror.h"
#include <glm/gtc/type_ptr.hpp>
#include <string>

using namespace engine;

Shader::Shader(OpenGlObject obj, GLenum type, const std::vector<VertexShaderAttribute>& attributes) :
    obj_(obj),
    type_(type),
    attributes_(attributes) {}

auto Shader::create(GLenum type, const std::string_view& path, std::vector<VertexShaderAttribute> attributes)
    -> Shader {

    dbgfln("Loading shader type %d from file: %s", type, path.data());
    auto source = common::file::read_file(path);

    auto shader = OpenGlObjectManager::instance().allocate(OpenGlObjectType::SHADER, type);

    dbgfln("Creating shader ID %d (shader_type=%d, attributes=%ld)", shader.ogl_id(), type, attributes.size());
    const char* const p = source.c_str();
    glShaderSource(shader.ogl_id(), 1, &p, nullptr);
    glCompileShader(shader.ogl_id());

    int success;
    glGetShaderiv(shader.ogl_id(), GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        constexpr size_t buffer_size{512};
        char log[buffer_size];
        glGetShaderInfoLog(shader.ogl_id(), buffer_size, nullptr, log);
        throw_gl("Compiling shader " + std::string(path) + " failed: " + std::string(log));
    }

    return {shader, type, attributes};
}

ShaderProgram::ShaderProgram(OpenGlObject obj,
                             const std::string& name,
                             const Shader& vertex_shader,
                             const Shader& fragment_shader) :
    obj_(obj),
    name_(name),
    vertex_shader_(vertex_shader),
    fragment_shader_(fragment_shader) {}

auto ShaderProgram::create(const std::string& name, const Shader& vertex_shader, const Shader& fragment_shader)
    -> ShaderProgram {
    XASSERTF(fragment_shader.is_fragment_shader(),
             "Shader ID {} not a fragment shader",
             fragment_shader.object().ogl_id());
    XASSERTF(vertex_shader.is_vertex_shader(), "Shader ID {} is not a vertex shader", vertex_shader.object().ogl_id());

    auto program = OpenGlObjectManager::instance().allocate(OpenGlObjectType::SHADER_PROGRAM);

    dbgfln("Creating shader program ID %d", program.ogl_id());
    glAttachShader(program.ogl_id(), vertex_shader.object().ogl_id());
    glAttachShader(program.ogl_id(), fragment_shader.object().ogl_id());

    dbgfln("Linking shader program ID %d", program.ogl_id());
    glLinkProgram(program.ogl_id());

    // we can free the shader GPU resources after attaching it
    // vertex_shader_.free_gpu_resources();
    // fragment_shader_.free_gpu_resources();

    int success;
    glGetProgramiv(program.ogl_id(), GL_LINK_STATUS, &success);
    if (success != GL_TRUE) {
        constexpr size_t buffer_size{512};
        char log[buffer_size];
        glGetProgramInfoLog(program.ogl_id(), buffer_size, nullptr, log);
        throw_gl("Linking shaders failed: " + std::string(log));
    }

    return {program, name, vertex_shader, fragment_shader};
}

auto ShaderProgram::query_attribute_location(const std::string_view& name) const -> GLint {
    auto location = glGetAttribLocation(obj_.ogl_id(), name.data());
    if (location < 0) {
        throw_gl("Attribute " + std::string(name) + " not found");
    }
    return location;
}

auto ShaderProgram::query_uniform_location(const std::string_view& name) const -> GLint {
    auto location = glGetUniformLocation(obj_.ogl_id(), name.data());
    if (location < 0) {
        throw_gl("Attribute " + std::string(name) + " not found");
    }
    return location;
}

void ShaderProgram::set_uniform(const std::string_view& name, glm::vec3 vec3) const {
    auto location = this->query_uniform_location(name);
    GL_CHECK(glUniform3f(location, vec3.r, vec3.g, vec3.b));
}

void ShaderProgram::set_uniform(const std::string_view& name, glm::mat4 mat4) const {
    auto location = this->query_uniform_location(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat4));
}

void ShaderProgram::bind() const {
    XASSERT(obj_.is_valid());
    glUseProgram(obj_.ogl_id());
}

void ShaderProgram::unbind() const {
    glUseProgram(0);
}

void ShaderProgram::customize(std::function<void(ShaderProgram&)> customizer) {
    bind();
    customizer(*this);
    unbind();
}

auto ShaderProgramRegistry::instance() -> ShaderProgramRegistry& {
    static ShaderProgramRegistry the_instance;
    return the_instance;
}

void ShaderProgramRegistry::set(Resource id, const ShaderProgram& shader_program) {
    XASSERT(id.type() == ResourceType::SHADER_PROGRAM);
    dbgfln("Consuming shader program ID %d to registry index %u", shader_program.object().ogl_id(), id.id());
    shader_program_map_.insert({id, shader_program});
}

auto ShaderProgramRegistry::get(Resource id) -> ShaderProgram& {
    XASSERT(id.type() == ResourceType::SHADER_PROGRAM);
    XASSERT(shader_program_map_.contains(id));
    return shader_program_map_[id];
}

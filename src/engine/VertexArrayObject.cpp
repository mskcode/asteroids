#include "VertexArrayObject.h"
#include "../common/debug.h"
#include "openglerror.h"
#include <memory>
#include <utility>

using namespace engine;

VertexArrayObject::VertexArrayObject(GLuint vao_id, ShaderProgram const* shader_program) :
    vao_id_(vao_id),
    shader_program_(shader_program) {}

VertexArrayObject::VertexArrayObject(VertexArrayObject&& other) noexcept :
    vao_id_(std::exchange(other.vao_id_, 0)),
    shader_program_(std::exchange(other.shader_program_, nullptr)),
    binding_index_(std::exchange(other.binding_index_, 0)) {}

VertexArrayObject::~VertexArrayObject() {
    free_gpu_resources();
}

auto VertexArrayObject::operator=(VertexArrayObject&& rhs) noexcept -> VertexArrayObject& {
    if (this != &rhs) {
        free_gpu_resources();
        vao_id_ = std::exchange(rhs.vao_id_, 0);
        shader_program_ = std::exchange(rhs.shader_program_, nullptr);
        binding_index_ = std::exchange(rhs.binding_index_, 0);
    }
    return *this;
}

auto VertexArrayObject::create(ShaderProgram const* shader_program) -> VertexArrayObject {
    GLuint vao_id;
    GL_CHECK(glCreateVertexArrays(1, &vao_id));

    // setup shader attributes (input variables) for VAO; we'll do the
    // attribute binding when we create VBOs
    auto& vertex_shader = shader_program->vertex_shader();
    for (auto& attr : vertex_shader.attributes()) {
        auto location = shader_program->query_attribute_location(attr.name);
        glEnableVertexArrayAttrib(vao_id, location);
        glVertexArrayAttribFormat(vao_id, location, attr.size, attr.type, attr.normalized, attr.relative_offset);
    }

    return VertexArrayObject{vao_id, shader_program};
}

auto VertexArrayObject::id() const -> GLuint {
    return vao_id_;
}

auto VertexArrayObject::is_valid() const -> bool {
    return vao_id_ > 0;
}

auto VertexArrayObject::shader_program() const -> const ShaderProgram& {
    return *shader_program_;
}

auto VertexArrayObject::create_vbo(GLsizeiptr buffer_size, GLsizei element_size, GLbitfield flags)
    -> VertexBufferObject {
    // create VBO
    GLuint vbo_id;
    GL_CHECK(glCreateBuffers(1, &vbo_id));

    // allocate memory to VBO
    GL_CHECK(glNamedBufferStorage(vbo_id, buffer_size, nullptr, flags));

    // attach VBO to this VAO; a VAO can have multiple VBOs attached hence we
    // have the running index indicating the attachment point
    GL_CHECK(glVertexArrayVertexBuffer(vao_id_, binding_index_, vbo_id, /*offset*/ 0, element_size));

    // bind shader attributes (input variables) to VAO
    auto& vertex_shader = shader_program_->vertex_shader();
    for (auto& attr : vertex_shader.attributes()) {
        auto location = shader_program_->query_attribute_location(attr.name);
        GL_CHECK(glVertexArrayAttribBinding(vao_id_, location, binding_index_));
    }

    ++binding_index_;

    return {vbo_id, buffer_size, element_size};
}

auto VertexArrayObject::create_ebo(GLsizeiptr buffer_size, GLbitfield flags) -> ElementBufferObject {
    // create EBO
    GLuint ebo_id;
    GL_CHECK(glCreateBuffers(1, &ebo_id));

    // allocate memory to EBO
    GL_CHECK(glNamedBufferStorage(ebo_id, buffer_size, nullptr, flags));

    // attach EBO to this VAO; only single EBO can be attached per VAO
    GL_CHECK(glVertexArrayElementBuffer(vao_id_, ebo_id));

    return {ebo_id, buffer_size};
}

void VertexArrayObject::free_gpu_resources() noexcept {
    if (vao_id_ > 0) {
        glDeleteVertexArrays(1, &vao_id_);
        vao_id_ = 0;
    }
}

void VertexArrayObject::bind() {
    glUseProgram(shader_program_->id());
    glBindVertexArray(vao_id_);
}

void VertexArrayObject::unbind() {
    glBindVertexArray(0);
    glUseProgram(0);
}

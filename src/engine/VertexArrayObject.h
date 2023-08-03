#pragma once

#include "ElementBufferObject.h"
#include "ShaderProgram.h"
#include "VertexBufferObject.h"
#include "opengl.h"

namespace engine {

class VertexArrayObject final {
public:
    VertexArrayObject() = default;
    VertexArrayObject(const VertexArrayObject&) = delete;
    VertexArrayObject(VertexArrayObject&& other) noexcept;
    ~VertexArrayObject();

    auto operator=(const VertexArrayObject&) -> VertexArrayObject& = delete;
    auto operator=(VertexArrayObject&& rhs) noexcept -> VertexArrayObject&;

    static auto create(ShaderProgram const* shader_program) -> VertexArrayObject;

    [[nodiscard]] auto id() const -> GLuint;
    [[nodiscard]] auto is_valid() const -> bool;
    [[nodiscard]] auto shader_program() const -> const ShaderProgram&;

    auto create_vbo(GLsizeiptr buffer_size, GLsizei element_size, GLbitfield flags) -> VertexBufferObject;
    auto create_ebo(GLsizeiptr buffer_size, GLbitfield flags) -> ElementBufferObject;

    void free_gpu_resources() noexcept;
    void bind();
    void unbind();

private:
    GLuint vao_id_{0};
    ShaderProgram const* shader_program_{nullptr};
    GLuint binding_index_{0};

    VertexArrayObject(GLuint vao_id, ShaderProgram const* shader_program);
};

} // namespace engine

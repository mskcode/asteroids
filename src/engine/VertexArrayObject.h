#pragma once

#include "ElementBufferObject.h"
#include "OpenGlObject.h"
#include "Shader.h"
#include "VertexBufferObject.h"
#include "opengl.h"

namespace engine {

class VertexArrayObject final {
public:
    VertexArrayObject() = default;
    VertexArrayObject(const VertexArrayObject&) = default;
    VertexArrayObject(VertexArrayObject&& other) noexcept = default;
    ~VertexArrayObject() = default;

    auto operator=(const VertexArrayObject&) -> VertexArrayObject& = default;
    auto operator=(VertexArrayObject&&) noexcept -> VertexArrayObject& = default;

    static auto create(const ShaderProgram& shader_program) -> VertexArrayObject;

    [[nodiscard]] auto object() const -> OpenGlObject { return vao_; }
    [[nodiscard]] auto shader_program() const -> const ShaderProgram& { return shader_program_; }

    auto create_vbo(GLsizeiptr buffer_size, GLsizei element_size, GLbitfield flags) -> VertexBufferObject;
    auto create_ebo(GLsizeiptr buffer_size, GLbitfield flags) -> ElementBufferObject;

    void bind();
    void unbind();

private:
    VertexArrayObject(OpenGlObject vao, const ShaderProgram& shader_program);

    OpenGlObject vao_;
    ShaderProgram shader_program_;
    GLuint binding_index_{0};
};

} // namespace engine

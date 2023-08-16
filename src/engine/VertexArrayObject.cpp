#include "VertexArrayObject.h"
#include "../common/assertions.h"
#include "openglerror.h"
#include <utility>

using namespace engine;

VertexArrayObject::VertexArrayObject(OpenGlObject vao, const ShaderProgram& shader_program) :
    vao_(vao),
    shader_program_(shader_program) {}

auto VertexArrayObject::create(const ShaderProgram& shader_program) -> VertexArrayObject {
    auto vao = OpenGlObjectManager::instance().allocate(OpenGlObjectType::VAO);

    // setup shader attributes (input variables) for VAO; we'll do the
    // attribute binding when we create VBOs
    auto& vertex_shader = shader_program.vertex_shader();
    for (auto& attr : vertex_shader.attributes()) {
        auto location = attr.location;
        if (location < 0) {
            XASSERTF(!attr.name.empty(),
                     "Shader program '{}' attribute is missing both location and name",
                     shader_program.name().c_str());
            location = shader_program.query_attribute_location(attr.name);
        }
        glEnableVertexArrayAttrib(vao.ogl_id(), location);
        glVertexArrayAttribFormat(vao.ogl_id(), location, attr.size, attr.type, attr.normalized, attr.relative_offset);
    }

    return VertexArrayObject{vao, shader_program};
}

auto VertexArrayObject::create_vbo(GLsizeiptr buffer_size, GLsizei element_size, GLbitfield flags)
    -> VertexBufferObject {
    auto vbo = OpenGlObjectManager::instance().allocate(OpenGlObjectType::VBO);

    // allocate memory to VBO
    GL_CHECK(glNamedBufferStorage(vbo.ogl_id(), buffer_size, nullptr, flags));

    // attach VBO to this VAO; a VAO can have multiple VBOs attached hence we
    // have the running index indicating the attachment point
    GL_CHECK(glVertexArrayVertexBuffer(vao_.ogl_id(), binding_index_, vbo.ogl_id(), /*offset*/ 0, element_size));

    // bind shader attributes (input variables) to VAO
    auto& vertex_shader = shader_program_.vertex_shader();
    for (auto& attr : vertex_shader.attributes()) {
        auto location = attr.location;
        if (location < 0) {
            XASSERTF(!attr.name.empty(),
                     "Shader program '{}' attribute is missing both location and name",
                     shader_program_.name().c_str());
            location = shader_program_.query_attribute_location(attr.name);
        }
        GL_CHECK(glVertexArrayAttribBinding(vao_.ogl_id(), location, binding_index_));
    }

    ++binding_index_;

    return {vbo, buffer_size, element_size};
}

auto VertexArrayObject::create_ebo(GLsizeiptr buffer_size, GLbitfield flags) -> ElementBufferObject {
    auto ebo = OpenGlObjectManager::instance().allocate(OpenGlObjectType::EBO);

    // allocate memory to EBO
    GL_CHECK(glNamedBufferStorage(ebo.ogl_id(), buffer_size, nullptr, flags));

    // attach EBO to this VAO; only single EBO can be attached per VAO
    GL_CHECK(glVertexArrayElementBuffer(vao_.ogl_id(), ebo.ogl_id()));

    return {ebo, buffer_size};
}

void VertexArrayObject::bind() {
    shader_program_.bind();
    glBindVertexArray(vao_.ogl_id());
}

void VertexArrayObject::unbind() {
    glBindVertexArray(0);
    shader_program_.unbind();
}

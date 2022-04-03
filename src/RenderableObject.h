#ifndef OPENGL_RENDERABLEOBJECT_H
#define OPENGL_RENDERABLEOBJECT_H

#include "ShaderProgramRegistry.h"
#include "debug.h"
#include "opengl.h"
#include <array>

namespace opengl {

struct Vertex3DPosition {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct VertexColor {
    GLfloat r;
    GLfloat g;
    GLfloat b;
};

struct Vertex3D {
    std::array<GLfloat, 3> position;
    std::array<GLfloat, 3> color;

    Vertex3D(Vertex3DPosition a_position, VertexColor a_color) {
        position[0] = a_position.x;
        position[1] = a_position.y;
        position[2] = a_position.z;
        color[0] = a_color.r;
        color[1] = a_color.g;
        color[2] = a_color.b;
    }
};

template <typename TType, size_t TSize>
class RenderableObject final {
public:
    RenderableObject(const ShaderProgramRegistry& spr, int shader_index) :
        buffer_size_(sizeof(TType) * TSize),
        shader_index_(shader_index),
        vao_(0),
        vbo_(0),
        index_count_(0) {
        glCreateBuffers(1, &vbo_);
        glNamedBufferStorage(vbo_, buffer_size_, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
        dbgfln("Created VBO ID %d with size %d", vbo_, buffer_size_);

        glCreateVertexArrays(1, &vao_);

        constexpr GLuint vertex_array_binding_point = 0;
        glVertexArrayVertexBuffer(vao_, vertex_array_binding_point, vbo_, /*offset*/ 0, sizeof(Vertex3D));

        auto& shader_program = spr.get(shader_index);
        auto& vertex_shader = shader_program.vertex_shader();
        for (auto& attr : vertex_shader.attributes()) {
            auto location = shader_program.query_attribute_location(attr.name);
            dbgfln("Binding shader attribute '%s' to location %d with offset %d",
                   attr.name.data(),
                   location,
                   attr.relative_offset);
            glEnableVertexArrayAttrib(vao_, location);
            glVertexArrayAttribFormat(vao_, location, attr.size, attr.type, attr.normalized, attr.relative_offset);
            glVertexArrayAttribBinding(vao_, location, vertex_array_binding_point);
        }
    }

    RenderableObject(const RenderableObject&) = delete;
    RenderableObject(RenderableObject&&) = delete;

    ~RenderableObject() { free_gpu_resources(); }

    auto operator=(const RenderableObject&) -> RenderableObject& = delete;
    auto operator=(RenderableObject&&) -> RenderableObject& = delete;

    void render(ShaderProgramRegistry& spr) {
        xassert(index_count_ > 0, "You're trying to render non-existing data");
        spr.get(shader_index_).bind();
        glBindVertexArray(vao_);
        glDrawArrays(GL_TRIANGLES, 0, index_count_);
        glBindVertexArray(0); // unbind
    }

    void update_data(const std::array<TType, TSize>& data) {
        glNamedBufferSubData(vbo_, 0, buffer_size_, data.data());
        index_count_ = data.size();
    }

    void free_gpu_resources() noexcept {
        if (vao_ > 0) {
            GLuint arrays[] = {vao_};
            glDeleteVertexArrays(1, arrays);
            vao_ = 0;
        }
        if (vbo_ > 0) {
            GLuint buffers[] = {vbo_};
            glDeleteBuffers(1, buffers);
            vbo_ = 0;
        }
    }

private:
    unsigned int buffer_size_;
    int shader_index_;
    GLuint vao_;
    GLuint vbo_;
    unsigned int index_count_;
};

} // namespace opengl

#endif // OPENGL_RENDERABLEOBJECT_H

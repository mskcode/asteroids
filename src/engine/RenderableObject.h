#ifndef ENGINE_RENDERABLEOBJECT_H
#define ENGINE_RENDERABLEOBJECT_H

#include "../common/debug.h"
#include "ShaderProgramRegistry.h"
#include "VertexArrayObject.h"
#include "opengl.h"
#include <array>

namespace engine {

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

class RenderableObject final {
public:
    RenderableObject(const ShaderProgram& shader_program) {
        vao_ = VertexArrayObject::create(&shader_program);
        vbo_ = vao_.create_vbo(1024, sizeof(Vertex3D), GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
    }

    RenderableObject(const RenderableObject&) = delete;
    RenderableObject(RenderableObject&&) noexcept = delete;
    ~RenderableObject() = default;

    auto operator=(const RenderableObject&) -> RenderableObject& = delete;
    auto operator=(RenderableObject&&) noexcept -> RenderableObject& = delete;

    [[nodiscard]] auto vbo() -> VertexBufferObject& {
        return vbo_;
    }

    void render() {
        vao_.bind();
        glDrawArrays(GL_TRIANGLES, 0, vbo_.element_count());
        vao_.unbind();
    }

private:
    VertexArrayObject vao_;
    VertexBufferObject vbo_;
};

} // namespace engine

#endif // ENGINE_RENDERABLEOBJECT_H

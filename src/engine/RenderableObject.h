#pragma once

#include "../common/debug.h"
#include "ShaderProgramRegistry.h"
#include "VertexArrayObject.h"
#include "opengl.h"
#include "types.h"
#include <array>

namespace engine {

class RenderableObject final {
public:
    RenderableObject(const ShaderProgram& shader_program) {
        vao_ = VertexArrayObject::create(&shader_program);
        vbo_ = vao_.create_vbo(1024, sizeof(Vertex), GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
        ebo_ = vao_.create_ebo(1024, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
    }

    RenderableObject(const RenderableObject&) = delete;
    RenderableObject(RenderableObject&&) noexcept = delete;
    ~RenderableObject() = default;

    auto operator=(const RenderableObject&) -> RenderableObject& = delete;
    auto operator=(RenderableObject&&) noexcept -> RenderableObject& = delete;

    [[nodiscard]] auto vbo() -> VertexBufferObject& { return vbo_; }
    [[nodiscard]] auto ebo() -> ElementBufferObject& { return ebo_; }

    void render() {
        vao_.bind();
        // glDrawArrays(GL_TRIANGLES, 0, vbo_.element_count());
        glDrawElements(GL_TRIANGLES, ebo_.indice_count(), GL_UNSIGNED_INT, nullptr);
        vao_.unbind();
    }

private:
    VertexArrayObject vao_;
    VertexBufferObject vbo_;
    ElementBufferObject ebo_;
};

} // namespace engine

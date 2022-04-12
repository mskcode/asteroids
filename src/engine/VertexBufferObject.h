#ifndef ENGINE_VERTEXBUFFEROBJECT_H
#define ENGINE_VERTEXBUFFEROBJECT_H

#include "opengl.h"

namespace engine {

class VertexArrayObject;

class VertexBufferObject final {
    friend class VertexArrayObject;

public:
    VertexBufferObject() = default;
    VertexBufferObject(const VertexBufferObject&) = delete;
    VertexBufferObject(VertexBufferObject&& other) noexcept;
    ~VertexBufferObject();

    auto operator=(const VertexBufferObject&) -> VertexBufferObject& = delete;
    auto operator=(VertexBufferObject&& rhs) noexcept -> VertexBufferObject&;

    [[nodiscard]] auto id() const -> GLuint;
    [[nodiscard]] auto buffer_size() const -> GLsizeiptr;
    [[nodiscard]] auto element_size() const -> GLsizei;
    [[nodiscard]] auto is_valid() const -> bool;

    void free_gpu_resources() noexcept;

private:
    GLuint vbo_id_{0};
    GLsizeiptr buffer_size_{0};
    GLsizei element_size_{0};
    
    VertexBufferObject(GLuint vbo_id, GLsizeiptr buffer_size, GLsizei element_size);
};

} // namespace engine

#endif // ENGINE_VERTEXBUFFEROBJECT_H

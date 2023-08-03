#pragma once

#include "opengl.h"
#include <array>

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
    [[nodiscard]] auto element_count() const -> GLsizei;
    [[nodiscard]] auto is_valid() const -> bool;

    void free_gpu_resources() noexcept;

    template <typename TType, size_t TSize>
    void set_data(std::array<TType, TSize> data, GLintptr offset = 0) {
        // TODO validate that we don't overflow the buffer
        glNamedBufferSubData(vbo_id_, offset, sizeof(data), data.data());
        element_count_ = data.size();
    }

private:
    GLuint vbo_id_{0};
    GLsizeiptr buffer_size_{0};
    GLsizei element_size_{0};
    GLsizei element_count_{0};

    VertexBufferObject(GLuint vbo_id, GLsizeiptr buffer_size, GLsizei element_size);
};

} // namespace engine

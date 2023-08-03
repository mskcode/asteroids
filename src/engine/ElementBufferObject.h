#pragma once

#include "opengl.h"
#include <array>

namespace engine {

class VertexArrayObject;

class ElementBufferObject final {
    friend class VertexArrayObject;

public:
    ElementBufferObject() = default;
    ElementBufferObject(const ElementBufferObject&) = delete;
    ElementBufferObject(ElementBufferObject&& other) noexcept;
    ~ElementBufferObject();

    auto operator=(const ElementBufferObject&) -> ElementBufferObject& = delete;
    auto operator=(ElementBufferObject&& rhs) noexcept -> ElementBufferObject&;

    [[nodiscard]] auto id() const -> GLuint;
    [[nodiscard]] auto is_valid() const -> bool;
    [[nodiscard]] auto indice_count() const -> GLsizei;

    void free_gpu_resources();

    template <size_t TSize>
    void set_data(std::array<GLuint, TSize> data, GLintptr offset = 0) {
        // TODO validate that we don't overflow the buffer
        glNamedBufferSubData(ebo_id_, offset, sizeof(data), data.data());
        indice_count_ = TSize;
    }

private:
    GLuint ebo_id_{0};
    GLsizeiptr buffer_size_{0};
    GLsizei indice_count_{0};

    ElementBufferObject(GLuint ebo_id, GLsizeiptr buffer_size);
};

} // namespace engine

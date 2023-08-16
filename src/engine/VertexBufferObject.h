#pragma once

#include "../common/assertions.h"
#include "OpenGlObject.h"
#include "opengl.h"
#include <array>

namespace engine {

class VertexArrayObject;

class VertexBufferObject final {
    friend class VertexArrayObject;

public:
    VertexBufferObject() = default;
    VertexBufferObject(const VertexBufferObject&) = default;
    VertexBufferObject(VertexBufferObject&& other) noexcept = default;
    ~VertexBufferObject() noexcept = default;

    auto operator=(const VertexBufferObject&) -> VertexBufferObject& = default;
    auto operator=(VertexBufferObject&&) noexcept -> VertexBufferObject& = default;

    [[nodiscard]] auto object() const -> OpenGlObject { return vbo_; }
    [[nodiscard]] auto buffer_size() const -> GLsizeiptr { return buffer_size_; }
    [[nodiscard]] auto element_size() const -> GLsizei { return element_size_; }
    [[nodiscard]] auto element_count() const -> GLsizei { return element_count_; }

    template <typename TType, size_t TSize>
    void set_data(std::array<TType, TSize> data, GLintptr offset = 0) {
        XASSERT(sizeof(data) <= (size_t)buffer_size_);
        glNamedBufferSubData(vbo_.ogl_id(), offset, sizeof(data), data.data());
        element_count_ = data.size();
    }

private:
    OpenGlObject vbo_;
    GLsizeiptr buffer_size_{0};
    GLsizei element_size_{0};
    GLsizei element_count_{0};

    VertexBufferObject(OpenGlObject vbo, GLsizeiptr buffer_size, GLsizei element_size);
};

} // namespace engine

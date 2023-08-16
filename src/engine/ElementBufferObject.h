#pragma once

#include "../common/assertions.h"
#include "OpenGlObject.h"
#include "opengl.h"
#include <array>

namespace engine {

class VertexArrayObject;

class ElementBufferObject final {
    friend class VertexArrayObject;

public:
    ElementBufferObject() = default;
    ElementBufferObject(const ElementBufferObject&) = default;
    ElementBufferObject(ElementBufferObject&& other) noexcept = default;
    ~ElementBufferObject() = default;

    auto operator=(const ElementBufferObject&) -> ElementBufferObject& = default;
    auto operator=(ElementBufferObject&&) noexcept -> ElementBufferObject& = default;

    [[nodiscard]] auto object() const -> OpenGlObject { return ebo_; }
    [[nodiscard]] auto indice_count() const -> GLsizei { return indice_count_; }

    template <size_t TSize>
    void set_data(std::array<GLuint, TSize> data, GLintptr offset = 0) {
        XASSERT(sizeof(data) <= (size_t)buffer_size_);
        glNamedBufferSubData(ebo_.ogl_id(), offset, sizeof(data), data.data());
        indice_count_ = TSize;
    }

private:
    OpenGlObject ebo_;
    GLsizeiptr buffer_size_{0};
    GLsizei indice_count_{0};

    ElementBufferObject(OpenGlObject ebo, GLsizeiptr buffer_size);
};

} // namespace engine

#include "VertexBufferObject.h"
#include <memory>

using namespace engine;

VertexBufferObject::VertexBufferObject(GLuint vbo_id, GLsizeiptr buffer_size, GLsizei element_size) :
    vbo_id_(vbo_id),
    buffer_size_(buffer_size),
    element_size_(element_size) {}

VertexBufferObject::VertexBufferObject(VertexBufferObject&& other) noexcept :
    vbo_id_(std::exchange(other.vbo_id_, 0)) {}

VertexBufferObject::~VertexBufferObject() {
    free_gpu_resources();
}

auto VertexBufferObject::operator=(VertexBufferObject&& rhs) noexcept -> VertexBufferObject& {
    if (this != &rhs) {
        free_gpu_resources();
        vbo_id_ = std::exchange(rhs.vbo_id_, 0);
        buffer_size_ = std::exchange(rhs.buffer_size_, 0);
        element_size_ = std::exchange(rhs.element_size_, 0);
    }
    return *this;
}

auto VertexBufferObject::id() const -> GLuint {
    return vbo_id_;
}

auto VertexBufferObject::buffer_size() const -> GLsizeiptr {
    return buffer_size_;
}

auto VertexBufferObject::element_size() const -> GLsizei {
    return element_size_;
}

auto VertexBufferObject::is_valid() const -> bool {
    return vbo_id_ > 0;
}

void VertexBufferObject::free_gpu_resources() noexcept {
    if (vbo_id_ > 0) {
        glDeleteBuffers(1, &vbo_id_);
        vbo_id_ = 0;
    }
}

#include "ElementBufferObject.h"
#include <memory>

using namespace engine;

ElementBufferObject::ElementBufferObject(GLuint ebo_id, GLsizeiptr buffer_size) :
    ebo_id_(ebo_id),
    buffer_size_(buffer_size) {}

ElementBufferObject::ElementBufferObject(ElementBufferObject&& other) noexcept :
    ebo_id_(std::exchange(other.ebo_id_, 0)),
    buffer_size_(std::exchange(other.buffer_size_, 0)) {}

ElementBufferObject::~ElementBufferObject() {
    free_gpu_resources();
}

auto ElementBufferObject::operator=(ElementBufferObject&& rhs) noexcept -> ElementBufferObject& {
    if (this != &rhs) {
        free_gpu_resources();
        ebo_id_ = std::exchange(rhs.ebo_id_, 0);
        buffer_size_ = std::exchange(rhs.buffer_size_, 0);
    }
    return *this;
}

auto ElementBufferObject::id() const -> GLuint {
    return ebo_id_;
}

auto ElementBufferObject::is_valid() const -> bool {
    return ebo_id_ > 0;
}

auto ElementBufferObject::indice_count() const -> GLsizei {
    return indice_count_;
}

void ElementBufferObject::free_gpu_resources() {
    if (ebo_id_ > 0) {
        glDeleteBuffers(1, &ebo_id_);
        ebo_id_ = 0;
    }
}

#include "VertexBufferObject.h"
#include <memory>
#include <utility>

using namespace engine;

VertexBufferObject::VertexBufferObject(OpenGlObject vbo, GLsizeiptr buffer_size, GLsizei element_size) :
    vbo_(vbo),
    buffer_size_(buffer_size),
    element_size_(element_size) {}

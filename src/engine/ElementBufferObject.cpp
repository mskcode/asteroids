#include "ElementBufferObject.h"
#include <memory>
#include <utility>

using namespace engine;

ElementBufferObject::ElementBufferObject(OpenGlObject ebo, GLsizeiptr buffer_size) :
    ebo_(ebo),
    buffer_size_(buffer_size) {}

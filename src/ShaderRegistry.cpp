#include "ShaderRegistry.h"
#include "debug.h"

using namespace opengl;

auto ShaderRegistry::instance() -> ShaderRegistry& {
    static ShaderRegistry the_instance;
    return the_instance;
}

void ShaderRegistry::set(int index, ShaderProgram&& shader) {
    dbgfln("Consuming shader program ID %d to registry index %d", shader.id(), index);
    registry_.insert(registry_.begin() + index, std::move(shader));
}

auto ShaderRegistry::get(int index) const -> const ShaderProgram& {
    return registry_[index];
}

void ShaderRegistry::use(int index) {
    if (index != currently_in_use_) {
        glUseProgram(registry_[index].id());
        currently_in_use_ = index;
    }
}

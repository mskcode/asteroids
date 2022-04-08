#include "ShaderProgramRegistry.h"
#include "../common/debug.h"

using namespace engine;

ShaderProgramRegistry::ShaderProgramRegistry() :
    shader_index_currently_in_use_(-1) {}

ShaderProgramRegistry::ShaderProgramRegistry(ShaderProgramRegistry&& other) noexcept :
    registry_(std::move(other.registry_)),
    shader_index_currently_in_use_(other.shader_index_currently_in_use_) {}

auto ShaderProgramRegistry::operator=(ShaderProgramRegistry&& rhs) noexcept -> ShaderProgramRegistry& {
    if (this != &rhs) {
        registry_ = std::move(rhs.registry_);
        shader_index_currently_in_use_ = std::exchange(rhs.shader_index_currently_in_use_, -1);
    }
    return *this;
}

void ShaderProgramRegistry::set(int index, ShaderProgram&& shader) {
    dbgfln("Consuming shader program ID %d to registry index %d", shader.id(), index);
    registry_.insert(registry_.begin() + index, std::move(shader));
}

auto ShaderProgramRegistry::get(int index) const -> const ShaderProgram& {
    return registry_[index];
}

void ShaderProgramRegistry::use(int index) {
    if (index != shader_index_currently_in_use_) {
        glUseProgram(registry_[index].id());
        shader_index_currently_in_use_ = index;
    }
}

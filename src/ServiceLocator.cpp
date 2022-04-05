#include "ServiceLocator.h"
#include "common/debug.h"

using namespace asteroids;

ServiceLocator::ServiceLocator() :
    key_event_dispatcher_(nullptr),
    shader_program_registry_(nullptr) {}

auto ServiceLocator::instance() -> ServiceLocator& {
    static ServiceLocator the_instance;
    return the_instance;
}

auto ServiceLocator::set_key_event_dispatcher(opengl::KeyEventDispatcher* key_event_dispatcher) -> ServiceLocator& {
    key_event_dispatcher_ = key_event_dispatcher;
    return *this;
}

auto ServiceLocator::set_shader_program_registry(opengl::ShaderProgramRegistry* shader_program_registry) -> ServiceLocator& {
    shader_program_registry_ = shader_program_registry;
    return *this;
}

auto ServiceLocator::key_event_dispatcher() const -> opengl::KeyEventDispatcher& {
    xassert(key_event_dispatcher_ != nullptr, "key_event_dispatcher_ is not set");
    return *key_event_dispatcher_;
}

auto ServiceLocator::shader_program_registry() const -> opengl::ShaderProgramRegistry& {
    xassert(shader_program_registry_ != nullptr, "shader_program_registry_ is not set");
    return *shader_program_registry_;
}

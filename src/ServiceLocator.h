#ifndef ASTEROIDS_SERVICELOCATOR_H
#define ASTEROIDS_SERVICELOCATOR_H

#include "opengl/KeyEventDispatcher.h"
#include "opengl/ShaderProgramRegistry.h"

namespace asteroids {

class ServiceLocator final {
public:
    static auto instance() -> ServiceLocator&;

    auto set_shader_program_registry(opengl::ShaderProgramRegistry* shader_program_registry) -> ServiceLocator&;
    auto set_key_event_dispatcher(opengl::KeyEventDispatcher* key_event_dispatcher) -> ServiceLocator&;

    [[nodiscard]] auto shader_program_registry() const -> opengl::ShaderProgramRegistry&;
    [[nodiscard]] auto key_event_dispatcher() const -> opengl::KeyEventDispatcher&;

private:
    opengl::KeyEventDispatcher* key_event_dispatcher_;
    opengl::ShaderProgramRegistry* shader_program_registry_;

    ServiceLocator();
};

} // namespace asteroids

#endif // ASTEROIDS_SERVICELOCATOR_H

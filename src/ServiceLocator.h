#pragma once

#include "engine/KeyEventDispatcher.h"
#include "engine/Shader.h"

namespace game {

class ServiceLocator final {
public:
    static auto instance() -> ServiceLocator&;

    auto set_shader_program_registry(engine::ShaderProgramRegistry* shader_program_registry) -> ServiceLocator&;
    auto set_key_event_dispatcher(engine::KeyEventDispatcher* key_event_dispatcher) -> ServiceLocator&;

    [[nodiscard]] auto shader_program_registry() const -> engine::ShaderProgramRegistry&;
    [[nodiscard]] auto key_event_dispatcher() const -> engine::KeyEventDispatcher&;

private:
    engine::KeyEventDispatcher* key_event_dispatcher_;
    engine::ShaderProgramRegistry* shader_program_registry_;

    ServiceLocator();
};

} // namespace game

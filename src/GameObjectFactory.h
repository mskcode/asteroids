#ifndef GAME_GAMEOBJECTFACTORY_H
#define GAME_GAMEOBJECTFACTORY_H

#include "GameActor.h"
#include "engine/Keyboard.h"
#include "engine/ShaderProgramRegistry.h"

namespace game {

class GameObjectFactory final {
public:
    GameObjectFactory(const engine::Keyboard& keyboard, engine::ShaderProgramRegistry& shader_program_registry);

    auto create_spaceship() -> GameActor*;

    auto renderables() const -> const std::vector<Renderable*>&;
    auto updateables() const -> const std::vector<Updateable*>&;

private:
    const engine::Keyboard& keyboard_;
    const engine::ShaderProgramRegistry& shader_program_registry_;
    std::vector<GameActor*> objects_;
    std::vector<Renderable*> renderables_;
    std::vector<Updateable*> updateables_;
};

} // namespace game

#endif // GAME_GAMEOBJECTFACTORY_H

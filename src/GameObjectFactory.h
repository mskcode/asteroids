#pragma once

#include "GameActor.h"
#include "engine/Keyboard.h"
#include "engine/Shader.h"

namespace game {

class GameObjectFactory final {
public:
    auto create_spaceship() -> GameActor*;

    auto renderables() const -> const std::vector<Renderable*>&;
    auto updateables() const -> const std::vector<Updateable*>&;

private:
    engine::TextureRegistry texture_registry_;
    std::vector<GameActor*> objects_;
    std::vector<Renderable*> renderables_;
    std::vector<Updateable*> updateables_;
};

} // namespace game

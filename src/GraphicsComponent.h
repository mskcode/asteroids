#pragma once

#include "GameComponent.h"
#include "engine/RenderableObject.h"
#include <memory>

namespace game {

class GameActor;

class GraphicsComponent : public GameComponent {
public:
    GraphicsComponent(std::unique_ptr<engine::RenderableObject> renderable_object);

    void render(const GameActor& game_actor);

private:
    std::unique_ptr<engine::RenderableObject> renderable_object_;
};

} // namespace game

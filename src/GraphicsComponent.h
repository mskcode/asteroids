#ifndef GAME_GRAPHICSCOMPONENT_H
#define GAME_GRAPHICSCOMPONENT_H

#include "GameComponent.h"
#include "engine/RenderableObject.h"

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

#endif // GAME_GRAPHICSCOMPONENT_H

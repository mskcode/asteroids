#ifndef ASTEROIDS_GRAPHICSCOMPONENT_H
#define ASTEROIDS_GRAPHICSCOMPONENT_H

#include "GameComponent.h"
#include "opengl/RenderableObject.h"

namespace asteroids {

class GameActor;

class GraphicsComponent : public GameComponent {
public:
    GraphicsComponent(std::unique_ptr<opengl::RenderableObject<opengl::Vertex3D, 3>> renderable_object);

    void render(const GameActor& game_actor);

private:
    std::unique_ptr<opengl::RenderableObject<opengl::Vertex3D, 3>> renderable_object_;
};

} // namespace asteroids

#endif // ASTEROIDS_GRAPHICSCOMPONENT_H

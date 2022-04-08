#ifndef ASTEROIDS_GAMEOBJECTFACTORY_H
#define ASTEROIDS_GAMEOBJECTFACTORY_H

#include "GameActor.h"
#include "opengl/Keyboard.h"
#include "opengl/ShaderProgramRegistry.h"

namespace asteroids {

class GameObjectFactory final {
public:
    GameObjectFactory(const opengl::Keyboard& keyboard, opengl::ShaderProgramRegistry& shader_program_registry);

    auto create_spaceship() -> GameActor*;

    auto renderables() const -> const std::vector<Renderable*>&;
    auto updateables() const -> const std::vector<Updateable*>&;

private:
    const opengl::Keyboard& keyboard_;
    const opengl::ShaderProgramRegistry& shader_program_registry_;
    std::vector<GameActor*> objects_;
    std::vector<Renderable*> renderables_;
    std::vector<Updateable*> updateables_;
};

} // namespace asteroids

#endif // ASTEROIDS_GAMEOBJECTFACTORY_H

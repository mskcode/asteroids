#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include "GameObjectFactory.h"
#include "Renderer.h"
#include "opengl/KeyEventDispatcher.h"
#include "opengl/Window.h"
#include <memory>

namespace asteroids {

class Game final {
public:
    Game(opengl::Window& window);
    ~Game() = default;

    void initialize();
    void loop();

private:
    opengl::Window& window_;
    opengl::KeyEventDispatcher key_event_dispatcher_;
    std::unique_ptr<opengl::ShaderProgramRegistry> shader_program_registry_;
    std::unique_ptr<GameObjectFactory> game_object_factory_;
    std::unique_ptr<Renderer> renderer_;
    bool stop_requested_ = false;
};

} // namespace asteroids

#endif // ASTEROIDS_GAME_H

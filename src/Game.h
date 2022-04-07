#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include "Renderer.h"
#include "Spaceship.h"
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
    Renderer renderer_;
    Spaceship* spaceship_;
    bool stop_requested_;
};

} // namespace asteroids

#endif // ASTEROIDS_GAME_H

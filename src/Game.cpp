#include "Game.h"
#include "ServiceLocator.h"

using namespace asteroids;

static auto load_shaders() -> std::unique_ptr<opengl::ShaderProgramRegistry> {
    using namespace opengl;
    dbgln("Loading shaders");

    ShaderProgram shader1{
        {GL_VERTEX_SHADER,
         "./resources/shaders/vertex.vert",
         {{"position", 3, GL_FLOAT, false, 0}, {"color", 3, GL_FLOAT, false, sizeof(float) * 3}}},
        {GL_FRAGMENT_SHADER, "./resources/shaders/fragment.frag"},
    };

    auto registry = std::make_unique<opengl::ShaderProgramRegistry>();
    registry->set(0, std::move(shader1));

    return registry;
}

Game::Game(opengl::Window& window) :
    window_(window),
    key_event_dispatcher_({window}),
    renderer_({window_}) {}

void Game::initialize() {
    key_event_dispatcher_.register_listener([&](auto event) {
        if (event.is_keypress(GLFW_KEY_ESCAPE)) {
            window_.close();
        }
    });

    key_event_dispatcher_.register_listener([&](auto event) {
        if (event.is_keypress(GLFW_KEY_F12)) {
            renderer_.toggle_wireframe_rendering();
        }
    });

    shader_program_registry_ = load_shaders();

    opengl::RenderableObject<opengl::Vertex3D, 3> renderable_object{*shader_program_registry_, 0};
    spaceship_ = new Spaceship(std::move(renderable_object), key_event_dispatcher_);

    renderer_.add_renderable(spaceship_);
}

void Game::loop() {
    while (!stop_requested_ && !window_.should_close()) {
        renderer_.render();

        glfwSwapBuffers(window_.window_pointer());
        glfwPollEvents();
    }
}

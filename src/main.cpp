#include "ServiceLocator.h"
#include "Spaceship.h"
#include "common/SignalHandler.h"
#include "common/debug.h"
#include "opengl/GlfwContext.h"
#include "opengl/KeyEventDispatcher.h"
#include "opengl/ShaderProgram.h"
#include "opengl/ShaderProgramRegistry.h"
#include "opengl/Window.h"
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>

static auto load_shaders() -> opengl::ShaderProgramRegistry {
    using namespace opengl;

    dbgln("Loading shaders");
    ShaderProgram shader1{
        {GL_VERTEX_SHADER,
         "./resources/shaders/vertex.vert",
         {{"position", 3, GL_FLOAT, false, 0}, {"color", 3, GL_FLOAT, false, sizeof(float) * 3}}},
        {GL_FRAGMENT_SHADER, "./resources/shaders/fragment.frag"},
    };

    ShaderProgramRegistry registry;
    registry.set(0, std::move(shader1));

    return registry;
}

auto main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) -> int {
    using namespace asteroids;

    opengl::GlfwContext glfw_context;
    common::SignalHandler signal_handler;

    try {
        opengl::Window window("Asteroids", 800, 600);
        signal_handler.register_listener([&window]([[maybe_unused]] auto signal) -> void { window.close(); },
                                         {SIGINT, SIGTERM});

        opengl::KeyEventDispatcher key_event_dispatcher{window};

        key_event_dispatcher.register_listener([&window](auto event) {
            if (event.action() == GLFW_PRESS) {
                switch (event.key()) {
                case GLFW_KEY_ESCAPE:
                    window.close();
                    break;
                case GLFW_KEY_F12:
                    window.toggle_wireframe_rendering();
                    break;
                default:
                    break;
                }
            }
        });

        auto shader_program_registry = load_shaders();

        ServiceLocator::instance()
            .set_key_event_dispatcher(&key_event_dispatcher)
            .set_shader_program_registry(&shader_program_registry);

        dbgln("Building spaceship");
        asteroids::Spaceship spaceship;

        window.run([&](auto window) -> bool {
            int width;
            int height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);

            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            spaceship.render();

            return true;
        });
    } catch (std::exception& e) {
        std::fprintf(stderr, "ERROR: %s\n", e.what());
        std::exit(1);
    }

    dbgln("Exiting program");
    return 0;
}

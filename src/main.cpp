#include "opengl/ShaderProgram.h"
#include "opengl/ShaderProgramRegistry.h"
#include "Spaceship.h"
#include "opengl/Window.h"
#include "common/debug.h"
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <functional>

std::function<void(int)> g_signal_handler_implementation;

static void signal_handler(int signum) {
    std::fprintf(stderr, "SIGNAL %d\n", signum);
    g_signal_handler_implementation(signum);
}

static auto load_shaders() -> opengl::ShaderProgramRegistry {
    using namespace opengl;

    dbgln("Loading shaders");
    opengl::ShaderProgram shader1{
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
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    try {
        opengl::Window window(800, 600);
        g_signal_handler_implementation = [&](int signum) {
            switch (signum) {
            case SIGINT:
            case SIGTERM:
                window.close();
            default:
                break;
            }
        };

        auto shader_program_registry = load_shaders();

        dbgln("Building spaceship");
        asteroids::Spaceship spaceship{shader_program_registry};

        window.on_key_event([&](auto event) {
            if (event.action() == GLFW_PRESS) {
                switch (event.key()) {
                case GLFW_KEY_ESCAPE:
                    window.close();
                    break;
                case GLFW_KEY_F12:
                    window.toggle_wireframe_rendering();
                    break;
                case GLFW_KEY_UP:
                    spaceship.move(0, 0.1f);
                    break;
                case GLFW_KEY_DOWN:
                    spaceship.move(0, -0.1f);
                    break;
                case GLFW_KEY_LEFT:
                    spaceship.move(-0.1f, 0);
                    break;
                case GLFW_KEY_RIGHT:
                    spaceship.move(0.1f, 0);
                    break;
                default:
                    break;
                }
            }
        });

        window.run([&](auto window) -> bool {
            int width;
            int height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);

            glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            spaceship.render(shader_program_registry);

            return true;
        });
    } catch (std::exception& e) {
        std::fprintf(stderr, "ERROR: %s\n", e.what());
        std::exit(1);
    }

    dbgln("Exiting program");
    return 0;
}

#include "ShaderProgram.h"
#include "ShaderRegistry.h"
#include "Spaceship.h"
#include "Window.h"
#include "debug.h"
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

static void load_shaders() {
    dbgln("Loading shaders");
    opengl::ShaderProgram shader1{
        {GL_VERTEX_SHADER,
         "./resources/shaders/vertex.vert",
         {{"position", 3, GL_FLOAT, false, 0}, {"color", 3, GL_FLOAT, false, 3}}},
        {GL_FRAGMENT_SHADER, "./resources/shaders/fragment.frag"},
    };

    opengl::ShaderRegistry::instance().set(0, std::move(shader1));
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

        load_shaders();

        dbgln("Building spaceship");
        asteroids::Spaceship spaceship;

        window.run([&](auto window) -> bool {
            int width;
            int height;
            glfwGetFramebufferSize(window, &width, &height);
            glViewport(0, 0, width, height);

            glClearColor(1.0F, 0.3F, 0.3F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);

            spaceship.render(window);

            return true;
        });
    } catch (std::exception& e) {
        std::fprintf(stderr, "ERROR: %s\n", e.what());
        std::exit(1);
    }

    dbgln("Exiting program");
    return 0;
}

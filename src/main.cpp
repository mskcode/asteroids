#include "Game.h"
#include "common/SignalHandler.h"
#include "common/debug.h"
#include "opengl/GlfwContext.h"
#include "opengl/Window.h"
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>

auto main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) -> int {
    using namespace asteroids;

    opengl::GlfwContext glfw_context;
    common::SignalHandler signal_handler;

    try {
        opengl::Window window("Asteroids", 1024, 768);
        signal_handler.register_listener([&window]([[maybe_unused]] auto signal) -> void { window.close(); },
                                         {SIGINT, SIGTERM});

        Game game{window};
        game.initialize();
        game.loop();
    } catch (std::exception& e) {
        std::fprintf(stderr, "ERROR: %s\n", e.what());
        std::exit(1);
    }

    dbgln("Exiting program");
    return 0;
}

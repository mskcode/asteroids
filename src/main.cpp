#include "Game.h"
#include "common/SignalHandler.h"
#include "common/debug.h"
#include "engine/GlfwContext.h"
#include "engine/Window.h"
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <exception>

auto main(int argc, char** argv) -> int {
    using namespace game;

    engine::GlfwContext glfw_context;
    common::SignalHandler signal_handler;

    try {
        engine::Window window({
            .title = "Moonlander 2.5D",
            .window_size = {.width = 1024, .height = 768},
            .resizable = false,
        });
        signal_handler.register_listener([&window](auto signal) -> void { window.close(); }, {SIGINT, SIGTERM});

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

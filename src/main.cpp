#include "GlWindow.h"

#include <cstdio>
#include <cstdlib>
#include <csignal>
#include <exception>
#include <functional>

using namespace asteroids;

std::function<void(int)> signal_handler_implementation;

static void signal_handler(int signum) {
    std::fprintf(stderr, "SIGNAL %d\n", signum);
    signal_handler_implementation(signum);

}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    try {
        GlWindow window(800, 600);
        signal_handler_implementation = [&](int signum) {
            switch (signum) {
                case SIGINT:
                case SIGTERM:
                    window.close();
                default:
                    break;
            }
        };

        window.run();
    } catch (std::exception &e) {
        std::fprintf(stderr, "ERROR: %s\n", e.what());
        std::exit(1);
    }
    return 0;
}

#include "SignalHandler.h"
#include "debug.h"
#include <csignal>

using namespace common;

static SignalHandler* g_signal_handler = nullptr;

static void signal_handler(int signum) {
    dbgfln("SIGNAL %d\n", signum);
    if (g_signal_handler != nullptr) {
        g_signal_handler->handle_signal(signum);
    }
}

SignalHandler::SignalHandler() {
    g_signal_handler = this;
}

void SignalHandler::register_listener(const std::function<void(const Signal&)>& listener, int signal_number) {
    std::signal(signal_number, signal_handler); // a bit wasteful, but oh well
    listeners_[signal_number].push_back(listener);
}

void SignalHandler::register_listener(const std::function<void(const Signal&)>& listener,
                                      const std::vector<int>& signal_numbers) {
    for (auto signal_number : signal_numbers) {
        this->register_listener(listener, signal_number);
    }
}

void SignalHandler::handle_signal(int signal_number) {
    if (listeners_.contains(signal_number)) {
        for (auto& listener : listeners_[signal_number]) {
            listener({signal_number});
        }
    }
}

#include "KeyEventDispatcher.h"
#include "../common/debug.h"

using namespace engine;

static KeyEventDispatcher* g_key_event_dispatcher;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // dbgfln("Key event: key=%d, scancode=%d, action=%d, mods=%d", key, scancode, action, mods);
    g_key_event_dispatcher->dispatch_event({window, key, scancode, action, mods});
}

KeyEventDispatcher::KeyEventDispatcher(const Window& window) {
    glfwSetKeyCallback(window.window_pointer(), ::key_callback);
    g_key_event_dispatcher = this;
}

auto KeyEventDispatcher::keyboard() const -> const Keyboard& {
    return keyboard_;
}

void KeyEventDispatcher::register_listener(const std::function<void(const KeyEvent&)>& listener) {
    listeners_.push_back(listener);
}

void KeyEventDispatcher::dispatch_event(const KeyEvent& event) {
    if (event.action() == GLFW_PRESS) {
        keyboard_[event.key()].set_down(true);
    } else if (event.action() == GLFW_RELEASE) {
        keyboard_[event.key()].set_down(false);
    }

    for (auto& listener : listeners_) {
        listener(event);
    }
}

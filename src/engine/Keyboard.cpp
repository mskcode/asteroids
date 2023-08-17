#include "Keyboard.h"

using namespace engine;

auto Keyboard::operator[](int key) -> KeyState& {
    return key_states_[key];
}

auto Keyboard::operator[](int key) const -> const KeyState& {
    return key_states_[key];
}

static Keyboard g_the_instance;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // dbgfln("Key event: key=%d, scancode=%d, action=%d, mods=%d", key, scancode, action, mods);
    g_the_instance.dispatch_event({window, key, scancode, action, mods});
}

auto Keyboard::instance() -> Keyboard& {
    return g_the_instance;
}

auto Keyboard::attach(const Window& window) -> void {
    glfwSetKeyCallback(window.window_pointer(), ::key_callback);
}

void Keyboard::register_listener(const std::function<void(const KeyEvent&)>& listener) {
    listeners_.push_back(listener);
}

void Keyboard::dispatch_event(const KeyEvent& event) {
    if (event.action() == GLFW_PRESS) {
        key_states_[event.key()].set_down(true);
    } else if (event.action() == GLFW_RELEASE) {
        key_states_[event.key()].set_down(false);
    }

    for (auto& listener : listeners_) {
        listener(event);
    }
}

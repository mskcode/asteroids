#include "Mouse.h"
#include "../common/debug.h"

using namespace engine;

auto Mouse::operator[](int key) -> MouseButtonState& {
    return button_states_[key];
}

auto Mouse::operator[](int key) const -> const MouseButtonState& {
    return button_states_[key];
}

void Mouse::set_position(Point2DL point) {
    current_.x = point.x;
    current_.y = point.y;
}

static Mouse g_the_mouse_instance;

static void mouse_position_callback(GLFWwindow* window, double xpos, double ypos) {
    // dbgfln("Mouse position event: xpos=%f, ypos=%f", xpos, ypos);
    g_the_mouse_instance.dispatch_event({window, (long)xpos, (long)ypos});
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    // dbgfln("Mouse button event: button=%d, action=%d, mods=%d", button, action, mods);
    g_the_mouse_instance.dispatch_event({window, button, action, mods});
}

auto Mouse::instance() -> Mouse& {
    return g_the_mouse_instance;
}

auto Mouse::attach(const Window& window) -> void {
    // hide mouse pointer
    glfwSetInputMode(window.window_pointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // enable raw mouse input when supported
    if (glfwRawMouseMotionSupported() == GLFW_TRUE) {
        dbgln("Enabling raw mouse input");
        glfwSetInputMode(window.window_pointer(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    // register callbacks
    glfwSetCursorPosCallback(window.window_pointer(), ::mouse_position_callback);
    glfwSetMouseButtonCallback(window.window_pointer(), ::mouse_button_callback);
}

void Mouse::register_listener(std::function<void(const MouseButtonEvent&)> listener) {
    button_listeners_.push_back(listener);
}

void Mouse::register_listener(std::function<void(const MousePositionEvent&)> listener) {
    position_listeners_.push_back(listener);
}

void Mouse::dispatch_event(const MouseButtonEvent& event) {
    if (event.action() == GLFW_PRESS) {
        button_states_[event.button()].set_down(true);
    } else if (event.action() == GLFW_RELEASE) {
        button_states_[event.button()].set_down(false);
    }

    for (auto& listener : button_listeners_) {
        listener(event);
    }
}

void Mouse::dispatch_event(const MousePositionEvent& event) {
    // the first mouse movements can jump wildly due to unknown reasons;
    // ignore the first few events just because of this
    ++position_event_count_;
    if (position_event_count_ < 3) {
        return;
    }

    set_position({event.xpos(), event.ypos()});
    for (auto& listener : position_listeners_) {
        listener(event);
    }
}

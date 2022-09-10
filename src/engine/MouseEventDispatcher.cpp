#include "MouseEventDispatcher.h"
#include "../common/debug.h"
#include "opengl.h"

using namespace engine;

static MouseEventDispatcher* g_mouse_event_dispatcher;

namespace {

void mouse_position_callback(GLFWwindow* window, double xpos, double ypos) {
    dbgfln("Mouse position event: xpos=%f, ypos=%f", xpos, ypos);
    g_mouse_event_dispatcher->dispatch_event({window, xpos, ypos});
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    // dbgfln("Mouse button event: button=%d, action=%d, mods=%d", button, action, mods);
    g_mouse_event_dispatcher->dispatch_event({window, button, action, mods});
}

} // namespace

MouseEventDispatcher::MouseEventDispatcher(const Window& window) {
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

    g_mouse_event_dispatcher = this;
}

auto MouseEventDispatcher::mouse() const -> const Mouse& {
    return mouse_;
}

void MouseEventDispatcher::register_listener(std::function<void(const MouseButtonEvent&)> listener) {
    button_listeners_.push_back(listener);
}

void MouseEventDispatcher::register_listener(std::function<void(const MousePositionEvent&)> listener) {
    position_listeners_.push_back(listener);
}

void MouseEventDispatcher::dispatch_event(const MouseButtonEvent& event) {
    if (event.action() == GLFW_PRESS) {
        mouse_[event.button()].set_down(true);
    } else if (event.action() == GLFW_RELEASE) {
        mouse_[event.button()].set_down(false);
    }

    for (auto& listener : button_listeners_) {
        listener(event);
    }
}

void MouseEventDispatcher::dispatch_event(const MousePositionEvent& event) {
    // the first mouse movements can jump wildly due to unknown reasons;
    // ignore the first few events just because of this
    ++position_event_count_;
    if (position_event_count_ < 3) {
        return;
    }

    mouse_.set_position({event.xpos(), event.ypos()});
    for (auto& listener : position_listeners_) {
        listener(event);
    }
}

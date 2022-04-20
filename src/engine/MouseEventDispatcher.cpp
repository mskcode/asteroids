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
    dbgfln("Mouse button event: button=%d, action=%d, mods=%d", button, action, mods);
    g_mouse_event_dispatcher->dispatch_event({window, button, action, mods});
}

} // namespace

MouseEventDispatcher::MouseEventDispatcher(const Window& window) {
    // capture mouse pointer
    glfwSetInputMode(window.window_pointer(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window.window_pointer(), ::mouse_position_callback);
    glfwSetMouseButtonCallback(window.window_pointer(), ::mouse_button_callback);
    g_mouse_event_dispatcher = this;
}

void MouseEventDispatcher::dispatch_event([[maybe_unused]] const MouseButtonEvent& event) {}

void MouseEventDispatcher::dispatch_event([[maybe_unused]] const MousePositionEvent& event) {}

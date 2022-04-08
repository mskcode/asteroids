#ifndef ENGINE_KEYEVENT_H
#define ENGINE_KEYEVENT_H

#include "opengl.h"

namespace engine {

class KeyEvent final {
public:
    KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) :
        window_(window),
        key_(key),
        scancode_(scancode),
        action_(action),
        mods_(mods) {}

    [[nodiscard]] auto window() const -> GLFWwindow* { return window_; }
    [[nodiscard]] auto key() const -> int { return key_; }
    [[nodiscard]] auto scancode() const -> int { return scancode_; }
    [[nodiscard]] auto action() const -> int { return action_; }
    [[nodiscard]] auto mods() const -> int { return mods_; }
    [[nodiscard]] auto is_keypress(int key) { return action_ == GLFW_PRESS && key_ == key; }

private:
    GLFWwindow* window_;
    int key_;
    int scancode_;
    int action_;
    int mods_;
};

} // namespace engine

#endif // ENGINE_KEYEVENT_H

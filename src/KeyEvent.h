#ifndef OPENGL_KEYEVENT_H
#define OPENGL_KEYEVENT_H

#include "opengl.h"

namespace opengl {

class KeyEvent final {
public:
    KeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) :
        window_(window),
        key_(key),
        scancode_(scancode),
        action_(action),
        mods_(mods) {}

    auto window() const -> GLFWwindow* { return window_; }
    auto key() const -> int { return key_; }
    auto scancode() const -> int { return scancode_; }
    auto action() const -> int { return action_; }
    auto mods() const -> int { return mods_; }

private:
    GLFWwindow* window_;
    int key_;
    int scancode_;
    int action_;
    int mods_;
};

} // namespace opengl

#endif // OPENGL_KEYEVENT_H

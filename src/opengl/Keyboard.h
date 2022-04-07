#ifndef OPENGL_KEYBOARD_H
#define OPENGL_KEYBOARD_H

#include "opengl.h"
#include <array>

namespace opengl {

class KeyState final {
public:
    [[nodiscard]] auto is_down() const -> bool { return down_; }

    void set_down(bool down) { down_ = down; }

private:
    bool down_ = false;
};

class Keyboard final {
public:
    Keyboard() = default;
    Keyboard(const Keyboard&) = delete;
    Keyboard(Keyboard&&) = delete;
    ~Keyboard() = default;

    auto operator=(const Keyboard&) -> Keyboard& = delete;
    auto operator=(Keyboard&&) -> Keyboard& = delete;

    auto operator[](int key) -> KeyState&;
    auto operator[](int key) const -> const KeyState&;

private:
    std::array<KeyState, GLFW_KEY_LAST> key_states_;
};

} // namespace opengl

#endif // OPENGL_KEYBOARD_H

#pragma once

#include "Window.h"
#include "opengl.h"
#include <array>
#include <functional>
#include <vector>

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
    [[nodiscard]] auto is_keypress(int key) const -> bool { return action_ == GLFW_PRESS && key_ == key; }

private:
    GLFWwindow* window_;
    int key_;
    int scancode_;
    int action_;
    int mods_;
};

class KeyState final {
public:
    [[nodiscard]] auto is_down() const -> bool { return down_; }
    void set_down(bool down) { down_ = down; }

private:
    bool down_{false};
};

class Keyboard final {
public:
    Keyboard() = default;
    Keyboard(const Keyboard&) = delete;
    Keyboard(Keyboard&&) = delete;
    ~Keyboard() = default;

    auto operator=(const Keyboard&) -> Keyboard& = delete;
    auto operator=(Keyboard&&) -> Keyboard& = delete;

    static auto instance() -> Keyboard&;

    auto operator[](int key) -> KeyState&;
    auto operator[](int key) const -> const KeyState&;

    auto attach(const Window& window) -> void;

    void register_listener(const std::function<void(const KeyEvent&)>& listener);
    void dispatch_event(const KeyEvent& event);

private:
    std::array<KeyState, GLFW_KEY_LAST> key_states_;
    std::vector<std::function<void(const KeyEvent&)>> listeners_;
};

} // namespace engine

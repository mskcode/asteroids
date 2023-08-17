#pragma once

#include "Window.h"
#include "opengl.h"
#include "types.h"
#include <array>
#include <functional>
#include <vector>

namespace engine {

class MouseButtonEvent final {
public:
    MouseButtonEvent(GLFWwindow* window, int button, int action, int mods) :
        window_(window),
        button_(button),
        action_(action),
        mods_(mods) {}

    [[nodiscard]] auto window() const -> GLFWwindow* { return window_; }
    [[nodiscard]] auto button() const -> int { return button_; }
    [[nodiscard]] auto action() const -> int { return action_; }
    [[nodiscard]] auto mods() const -> int { return mods_; }

private:
    GLFWwindow* window_;
    int button_;
    int action_;
    int mods_;
};

class MousePositionEvent final {
public:
    MousePositionEvent(GLFWwindow* window, long xpos, long ypos) :
        window_(window),
        x_(xpos),
        y_(ypos) {}

    [[nodiscard]] auto window() const -> GLFWwindow* { return window_; }
    [[nodiscard]] auto xpos() const -> long { return x_; }
    [[nodiscard]] auto ypos() const -> long { return y_; }

private:
    GLFWwindow* window_;
    long x_;
    long y_;
};

class MouseButtonState final {
public:
    [[nodiscard]] auto is_down() const -> bool { return down_; }
    void set_down(bool down) { down_ = down; }

private:
    bool down_{false};
};

class Mouse final {
public:
    Mouse() = default;
    Mouse(const Mouse&) = delete;
    Mouse(Mouse&&) noexcept = delete;
    ~Mouse() = default;

    auto operator=(const Mouse&) -> Mouse& = delete;
    auto operator=(Mouse&&) noexcept -> Mouse& = delete;

    static auto instance() -> Mouse&;

    auto operator[](int key) -> MouseButtonState&;
    auto operator[](int key) const -> const MouseButtonState&;

    [[nodiscard]] auto position() const -> Point2DL { return current_; }
    auto set_position(Point2DL point) -> void;

    auto attach(const Window& window) -> void;

    auto register_listener(std::function<void(const MouseButtonEvent&)> listener) -> void;
    auto register_listener(std::function<void(const MousePositionEvent&)> listener) -> void;
    auto dispatch_event(const MouseButtonEvent& event) -> void;
    auto dispatch_event(const MousePositionEvent& event) -> void;

private:
    Point2DL current_; // current position
    std::array<MouseButtonState, GLFW_MOUSE_BUTTON_LAST> button_states_;
    std::vector<std::function<void(const MouseButtonEvent&)>> button_listeners_;
    std::vector<std::function<void(const MousePositionEvent&)>> position_listeners_;
    uint64_t position_event_count_{0};
};

} // namespace engine

#pragma once

#include "Mouse.h"
#include "Window.h"
#include <functional>

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

class MouseEventDispatcher final {
public:
    explicit MouseEventDispatcher(const Window& window);
    MouseEventDispatcher(const MouseEventDispatcher&) = delete;
    MouseEventDispatcher(MouseEventDispatcher&&) noexcept = delete;
    ~MouseEventDispatcher() = default;

    auto operator=(const MouseEventDispatcher&) -> MouseEventDispatcher& = delete;
    auto operator=(MouseEventDispatcher&&) noexcept -> MouseEventDispatcher& = delete;

    [[nodiscard]] auto mouse() const -> const Mouse&;

    void register_listener(std::function<void(const MouseButtonEvent&)> listener);
    void register_listener(std::function<void(const MousePositionEvent&)> listener);
    void dispatch_event(const MouseButtonEvent& event);
    void dispatch_event(const MousePositionEvent& event);

private:
    Mouse mouse_;
    std::vector<std::function<void(const MouseButtonEvent&)>> button_listeners_;
    std::vector<std::function<void(const MousePositionEvent&)>> position_listeners_;
    uint64_t position_event_count_{0};
};

} // namespace engine

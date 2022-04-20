#ifndef ENGINE_MOUSEEVENTDISPATCHER_H
#define ENGINE_MOUSEEVENTDISPATCHER_H

#include "Window.h"

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
    MousePositionEvent(GLFWwindow* window, double xpos, double ypos) :
        window_(window),
        xpos_(xpos),
        ypos_(ypos) {}

    [[nodiscard]] auto get_window() const -> GLFWwindow* { return window_; }
    [[nodiscard]] auto get_xpos() const -> double { return xpos_; }
    [[nodiscard]] auto get_ypos() const -> double { return ypos_; }

private:
    GLFWwindow* window_;
    double xpos_;
    double ypos_;
};

class MouseEventDispatcher final {
public:
    explicit MouseEventDispatcher(const Window& window);
    MouseEventDispatcher(const MouseEventDispatcher&) = delete;
    MouseEventDispatcher(MouseEventDispatcher&&) noexcept = delete;
    ~MouseEventDispatcher() = default;

    auto operator=(const MouseEventDispatcher&) -> MouseEventDispatcher& = delete;
    auto operator=(MouseEventDispatcher&&) noexcept -> MouseEventDispatcher& = delete;

    void dispatch_event(const MouseButtonEvent& event);
    void dispatch_event(const MousePositionEvent& event);

private:
    std::vector<std::function<void(const MouseButtonEvent&)>> button_listeners_;
};

} // namespace engine

#endif // ENGINE_MOUSEEVENTDISPATCHER_H

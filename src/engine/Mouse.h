#ifndef ENGINE_MOUSE_H
#define ENGINE_MOUSE_H

#include "opengl.h"
#include "types.h"
#include <array>

namespace engine {

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

    auto operator[](int key) -> MouseButtonState&;
    auto operator[](int key) const -> const MouseButtonState&;

    [[nodiscard]] auto position() const -> Point2DD;

    void set_initial_position(Point2DD point);
    void set_position(Point2DD point);

private:
    Point2DD initial_; // position when program starts
    Point2DD current_; // current position
    std::array<MouseButtonState, GLFW_MOUSE_BUTTON_LAST> button_states_;
};

} // namespace engine

#endif // ENGINE_MOUSE_H

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
    [[nodiscard]] auto x_position() const -> double;
    [[nodiscard]] auto y_position() const -> double;

    void set_position(double x, double y);

private:
    double x_position_;
    double y_position_;
    std::array<MouseButtonState, GLFW_MOUSE_BUTTON_LAST> button_states_;
};

} // namespace engine

#endif // ENGINE_MOUSE_H

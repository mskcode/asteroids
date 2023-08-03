#pragma once

#include "CameraDirector.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace engine {

class MouseKeyboardCameraDirector : public CameraDirector {
public:
    MouseKeyboardCameraDirector(const Mouse& mouse, const Keyboard& keyboard);

    void update() override;

    [[nodiscard]] auto front() const -> glm::vec3 override { return front_; }
    [[nodiscard]] auto right() const -> glm::vec3 override { return right_; }
    [[nodiscard]] auto up() const -> glm::vec3 override { return up_; }
    [[nodiscard]] auto position() const -> glm::vec3 override { return position_; }

private:
    const engine::Mouse& mouse_;
    const engine::Keyboard& keyboard_;
    const glm::vec3 world_up_{0.0f, 1.0f, 0.0f};
    glm::vec3 front_{0.0f, 0.0f, -1.0f};
    glm::vec3 up_{0.0f, 1.0f, 0.0f};
    glm::vec3 right_{0.0f, 0.0f, 0.0f};
    glm::vec3 position_{0.0f, 0.0f, 2.0f};
    float pitch_{0.0f}; // how much we're looking up or down
    float yaw_{-90.0f}; // magnitude of looking left or right
    engine::Point2DL mouse_last_position_;
    float mouse_look_sensitivity_{0.05f};
    float kbd_move_velocity_{0.05f};
};

} // namespace engine

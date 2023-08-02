#include "MouseKeyboardCameraDirector.h"
#include <glm/ext/matrix_clip_space.hpp>

using namespace engine;

namespace {

static auto compute_camera_direction_offset(engine::Point2DL last, engine::Point2DL current, float sensitivity)
    -> engine::Point2DF {
    if (last.x == 0 && last.y == 0) {
        // when last position is dead zero, assume that the (mouse) position
        // hasn't been updated correctly yet
        return {0.0f, 0.0f};
    }

    auto x_offset = static_cast<float>(current.x - last.x);
    auto y_offset = static_cast<float>(last.y - current.y); // reversed since y-coords range from bottom to top

    x_offset = x_offset * sensitivity;
    y_offset = y_offset * sensitivity;

    return {x_offset, y_offset};
}

template <typename T>
static auto clamp(T current, T min, T max) -> T {
    if (current < min) {
        return min;
    }
    if (current > max) {
        return max;
    }
    return current;
}

} // namespace

MouseKeyboardCameraDirector::MouseKeyboardCameraDirector(const Mouse& mouse, const Keyboard& keyboard) :
    mouse_(mouse),
    keyboard_(keyboard) {}

void MouseKeyboardCameraDirector::update() {
    auto mouse_current_position = mouse_.position();
    auto offset = ::compute_camera_direction_offset(mouse_last_position_,
                                                    mouse_current_position,
                                                    mouse_look_sensitivity_);
    mouse_last_position_ = mouse_current_position;

    yaw_ += offset.x;
    pitch_ += ::clamp((float)offset.y, -89.0f, 89.0f);

    if (keyboard_[GLFW_KEY_W].is_down()) { // move forward
        position_ += front_ * kbd_move_velocity_;
    }
    if (keyboard_[GLFW_KEY_S].is_down()) { // move backward
        position_ -= front_ * kbd_move_velocity_;
    }
    if (keyboard_[GLFW_KEY_A].is_down()) { // strafe left
        position_ -= right_ * kbd_move_velocity_;
    }
    if (keyboard_[GLFW_KEY_D].is_down()) { // strafe right
        position_ += right_ * kbd_move_velocity_;
    }
    if (keyboard_[GLFW_KEY_SPACE].is_down()) { // ascend
        position_ += up_ * kbd_move_velocity_;
    }
    if (keyboard_[GLFW_KEY_LEFT_CONTROL].is_down()) { // descend
        position_ -= up_ * kbd_move_velocity_;
    }

    glm::vec3 front;
    front.x = glm::cos(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
    front.y = glm::sin(glm::radians(pitch_));
    front.z = glm::sin(glm::radians(yaw_)) * glm::cos(glm::radians(pitch_));
    front_ = glm::normalize(front);

    // normalize the vectors, because their length gets closer to 0
    // the more you look up or down which results in slower movement.
    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));
}

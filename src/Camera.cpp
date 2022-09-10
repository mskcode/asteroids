#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <glm/mat4x4.hpp>

using namespace game;

static auto compute_camera_direction_offset(engine::Point2DD last, engine::Point2DD current) -> engine::Point2DD {
    double x_offset = current.x - last.x;
    double y_offset = last.y - current.y; // reversed since y-coords range from bottom to top

    constexpr float sensitivity = 0.01f;
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

Camera::Camera(const engine::Keyboard& keyboard,
               const engine::Mouse& mouse,
               const engine::ShaderProgram& shader_program,
               std::string shader_camera_matrix_name) :
    keyboard_(keyboard),
    mouse_(mouse),
    shader_program_(shader_program),
    shader_camera_matrix_name_(std::move(shader_camera_matrix_name)) {}

void Camera::update() {
    auto current_mouse_position = mouse_.position();
    auto offset = compute_camera_direction_offset(last_mouse_position_, current_mouse_position);
    last_mouse_position_ = current_mouse_position;

    yaw_ += (float)offset.x;
    pitch_ += (float)offset.y;
    pitch_ = clamp(pitch_, -89.0f, 89.0f);

    constexpr float velocity = 0.05f;
    // constexpr float turn_velocity = 1.0f;
    if (keyboard_[GLFW_KEY_W].is_down()) { // move forward
        position_ += front_ * velocity;
    }
    if (keyboard_[GLFW_KEY_S].is_down()) { // move backward
        position_ -= front_ * velocity;
    }
    if (keyboard_[GLFW_KEY_A].is_down()) { // strafe left
        position_ -= right_ * velocity;
    }
    if (keyboard_[GLFW_KEY_D].is_down()) { // strafe right
        position_ += right_ * velocity;
    }
    /* if (keyboard_[GLFW_KEY_A].is_down()) { // turn camera left
        yaw_ -= turn_velocity;
    }
    if (keyboard_[GLFW_KEY_D].is_down()) { // turn camera right
        yaw_ += turn_velocity;
    } */
    if (keyboard_[GLFW_KEY_SPACE].is_down()) { // ascend
        position_ += up_ * velocity;
    }
    if (keyboard_[GLFW_KEY_LEFT_CONTROL].is_down()) { // descend
        position_ -= up_ * velocity;
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

    shader_update_needed_ = true;
}

/**
 * Read about perspective: https://knowww.eu/nodes/59b8e93cd54a862e9d7e40e3
 */
void Camera::update_shader_matrix() {
    if (!shader_update_needed_) {
        return;
    }

    // set camera direction
    auto view = glm::lookAt(position_, position_ + front_, up_);

    // add perspective to scene
    auto aspect_ratio = float(window_dimensions_.width) / window_dimensions_.height;
    auto projection = glm::perspective(glm::radians(field_of_view_degrees_), aspect_ratio, near_plane_, far_plane_);

    auto matrix = projection * view;
    shader_program_.bind();
    shader_program_.set_uniform(shader_camera_matrix_name_, matrix);
    shader_program_.unbind();

    shader_update_needed_ = false;
}

void Camera::set_window_dimensions(engine::Dimensions2D window_dimensions) {
    window_dimensions_ = window_dimensions;
    shader_update_needed_ = true;
}

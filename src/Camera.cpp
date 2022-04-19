#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <glm/mat4x4.hpp>

using namespace game;

Camera::Camera(const engine::Keyboard& keyboard,
               const engine::ShaderProgram& shader_program,
               std::string shader_camera_matrix_name) :
    keyboard_(keyboard),
    shader_program_(shader_program),
    shader_camera_matrix_name_(std::move(shader_camera_matrix_name)) {}

void Camera::update() {
    constexpr float velocity = 0.05f;
    constexpr float turn_velocity = 1.0f;
    if (keyboard_[GLFW_KEY_W].is_down()) { // move forward
        position_ += front_ * velocity;
    }
    if (keyboard_[GLFW_KEY_S].is_down()) { // move backward
        position_ -= front_ * velocity;
    }
    if (keyboard_[GLFW_KEY_Q].is_down()) { // strafe left
        position_ -= right_ * velocity;
    }
    if (keyboard_[GLFW_KEY_E].is_down()) { // strafe right
        position_ += right_ * velocity;
    }
    if (keyboard_[GLFW_KEY_A].is_down()) { // turn camera left
        yaw_ -= turn_velocity;
    }
    if (keyboard_[GLFW_KEY_D].is_down()) { // turn camera right
        yaw_ += turn_velocity;
    }
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

    right_ =
        glm::normalize(glm::cross(front_, world_up_)); // normalize the vectors, because their length gets closer to 0
                                                       // the more you look up or down which results in slower movement.
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

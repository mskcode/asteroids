#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <cmath>
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
        position_.z -= velocity;
        shader_update_needed_ = true;
    }
    if (keyboard_[GLFW_KEY_S].is_down()) { // move backward
        position_.z += velocity;
        shader_update_needed_ = true;
    }
    if (keyboard_[GLFW_KEY_Q].is_down()) { // strafe left
        // cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        position_ -= glm::normalize(glm::cross(orientation_, up_)) * velocity;
        shader_update_needed_ = true;
    }
    if (keyboard_[GLFW_KEY_E].is_down()) { // strafe right
        position_ += glm::normalize(glm::cross(orientation_, up_)) * velocity;
        shader_update_needed_ = true;
    }
    if (keyboard_[GLFW_KEY_A].is_down()) { // turn camera left
        yaw_ -= turn_velocity;
        shader_update_needed_ = true;
    }
    if (keyboard_[GLFW_KEY_D].is_down()) { // turn camera right
        yaw_ += turn_velocity;
        shader_update_needed_ = true;
    }

    glm::vec3 direction;
    direction.x = std::cos(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
    direction.y = std::sin(glm::radians(pitch_));
    direction.z = std::sin(glm::radians(yaw_)) * std::cos(glm::radians(pitch_));
    orientation_ = glm::normalize(direction);
}

/**
 * Read about perspective: https://knowww.eu/nodes/59b8e93cd54a862e9d7e40e3
 */
void Camera::update_shader_matrix() {
    if (!shader_update_needed_) {
        return;
    }

    // set camera direction
    auto view = glm::lookAt(position_, position_ + orientation_, up_);

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

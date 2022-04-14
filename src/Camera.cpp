#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <glm/mat4x4.hpp>

using namespace game;

Camera::Camera(engine::ShaderProgram& shader_program, std::string shader_camera_matrix_name) :
    shader_program_(shader_program),
    shader_camera_matrix_name_(std::move(shader_camera_matrix_name)) {}

auto Camera::position() const -> glm::vec3 {
    return position_;
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

void Camera::set_position(glm::vec3 position) {
    position_ = position;
    shader_update_needed_ = true;
}

#include "Camera.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <glm/mat4x4.hpp>

using namespace game;

Camera::Camera(const engine::CameraDirector& camera_director,
               const engine::ShaderProgram& shader_program,
               std::string shader_camera_matrix_name) :
    camera_director_(camera_director),
    shader_program_(shader_program),
    shader_camera_matrix_name_(std::move(shader_camera_matrix_name)) {}

/**
 * Read about perspective: https://knowww.eu/nodes/59b8e93cd54a862e9d7e40e3
 */
void Camera::update_shader_matrix() {
    auto position = camera_director_.position();
    auto front = camera_director_.front();
    auto up = camera_director_.up();

    // set camera direction
    auto view = glm::lookAt(position, position + front, up);

    // add perspective to scene
    auto aspect_ratio = float(window_dimensions_.width) / (float)window_dimensions_.height;
    auto projection = glm::perspective(glm::radians(field_of_view_degrees_), aspect_ratio, near_plane_, far_plane_);

    auto matrix = projection * view;
    shader_program_.bind();
    shader_program_.set_uniform(shader_camera_matrix_name_, matrix);
    shader_program_.unbind();
}

void Camera::set_window_dimensions(engine::Dimensions2D window_dimensions) {
    window_dimensions_ = window_dimensions;
}

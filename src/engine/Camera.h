#pragma once

#include "CameraDirector.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Shader.h"
#include "glm/vec3.hpp"
#include "types.h"
#include <memory>
#include <string>

namespace engine {

class Camera final {
public:
    Camera(const CameraDirector& camera_director,
           Resource shader_program_resource,
           std::string shader_camera_matrix_name);
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;
    ~Camera() = default;

    auto operator=(const Camera&) -> Camera& = delete;
    auto operator=(Camera&&) -> Camera& = delete;

    void update_shader_matrix();
    void set_window_dimensions(Dimensions2D window_dimensions);

private:
    const CameraDirector& camera_director_;
    Resource shader_program_resource_;
    const std::string shader_camera_matrix_name_;
    Dimensions2D window_dimensions_;
    float field_of_view_degrees_{45.0f};
    float near_plane_{0.1f};
    float far_plane_{100.0f};
};

} // namespace engine

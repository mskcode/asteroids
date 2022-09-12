#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include "engine/CameraDirector.h"
#include "engine/Keyboard.h"
#include "engine/Mouse.h"
#include "engine/ShaderProgram.h"
#include "engine/types.h"
#include <glm/vec3.hpp>
#include <memory>
#include <string>

namespace game {

class Camera final {
public:
    Camera(const engine::CameraDirector& camera_director,
           const engine::ShaderProgram& shader_program,
           std::string shader_camera_matrix_name);
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;
    ~Camera() = default;

    auto operator=(const Camera&) -> Camera& = delete;
    auto operator=(Camera&&) -> Camera& = delete;

    void update_shader_matrix();
    void set_window_dimensions(engine::Dimensions2D window_dimensions);

private:
    const engine::CameraDirector& camera_director_;
    const engine::ShaderProgram& shader_program_;
    const std::string shader_camera_matrix_name_;
    engine::Dimensions2D window_dimensions_;
    float field_of_view_degrees_{45.0f};
    float near_plane_{0.1f};
    float far_plane_{100.0f};
};

} // namespace game

#endif // GAME_CAMERA_H

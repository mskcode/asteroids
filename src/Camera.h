#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include "engine/ShaderProgram.h"
#include "engine/types.h"
#include <glm/vec3.hpp>
#include <string>

namespace game {

class Camera final {
public:
    Camera(engine::ShaderProgram& shader_program, std::string shader_camera_matrix_name);
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;
    ~Camera() = default;

    auto operator=(const Camera&) -> Camera& = delete;
    auto operator=(Camera&&) -> Camera& = delete;

    [[nodiscard]] auto position() const -> glm::vec3;

    void update_shader_matrix();
    void set_window_dimensions(engine::Dimensions2D window_dimensions);
    void set_position(glm::vec3 position);

private:
    engine::ShaderProgram& shader_program_;
    const std::string shader_camera_matrix_name_;
    engine::Dimensions2D window_dimensions_;
    glm::vec3 position_{0.0f, 0.0f, 2.0f};
    glm::vec3 orientation_{0.0f, 0.0f, -1.0f};
    const glm::vec3 up_{0.0f, 1.0f, 0.0f};
    float field_of_view_degrees_{45.0f};
    float near_plane_{0.1f};
    float far_plane_{100.0f};
    bool shader_update_needed_{true};
};

} // namespace game

#endif // GAME_CAMERA_H

#ifndef GAME_CAMERA_H
#define GAME_CAMERA_H

#include "Updateable.h"
#include "engine/Keyboard.h"
#include "engine/Mouse.h"
#include "engine/ShaderProgram.h"
#include "engine/types.h"
#include <glm/vec3.hpp>
#include <memory>
#include <string>

namespace game {

class Camera final : public Updateable {
public:
    Camera(const engine::Keyboard& keyboard,
           const engine::Mouse& mouse,
           const engine::ShaderProgram& shader_program,
           std::string shader_camera_matrix_name);
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;
    ~Camera() = default;

    auto operator=(const Camera&) -> Camera& = delete;
    auto operator=(Camera&&) -> Camera& = delete;

    void update() override;
    void update_shader_matrix();
    void set_window_dimensions(engine::Dimensions2D window_dimensions);

private:
    const engine::Keyboard& keyboard_;
    const engine::Mouse& mouse_;
    const engine::ShaderProgram& shader_program_;
    const std::string shader_camera_matrix_name_;
    engine::Dimensions2D window_dimensions_;
    glm::vec3 position_{0.0f, 0.0f, 2.0f};
    glm::vec3 front_{0.0f, 0.0f, -1.0f};
    glm::vec3 up_{0.0f, 1.0f, 0.0f};
    glm::vec3 world_up_{0.0f, 1.0f, 0.0f};
    glm::vec3 right_{0.0f, 0.0f, 0.0f};
    float pitch_{0.0f}; // how much we're looking up or down
    float yaw_{-90.0f}; // magnitude of looking left or right
    float field_of_view_degrees_{45.0f};
    float near_plane_{0.1f};
    float far_plane_{100.0f};
    bool shader_update_needed_{true};
    engine::Point2DD last_mouse_position_;
};

} // namespace game

#endif // GAME_CAMERA_H

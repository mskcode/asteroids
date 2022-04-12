#ifndef ENGINE_SHADERPROGRAM_H
#define ENGINE_SHADERPROGRAM_H

#include "Shader.h"
#include "glm/vec3.hpp"
#include "opengl.h"
#include <functional>
#include <string_view>
#include <vector>

namespace engine {

class ShaderProgram final {
public:
    ShaderProgram(Shader vertex_shader, Shader fragment_shader);
    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram(ShaderProgram&& other) noexcept;
    ~ShaderProgram();

    auto operator=(const ShaderProgram&) -> ShaderProgram& = delete;
    auto operator=(ShaderProgram&& rhs) noexcept -> ShaderProgram&;

    [[nodiscard]] auto id() const -> GLuint;
    [[nodiscard]] auto vertex_shader() const -> const Shader&;
    [[nodiscard]] auto fragment_shader() const -> const Shader&;
    [[nodiscard]] auto query_attribute_location(const std::string_view& name) const -> GLint;
    [[nodiscard]] auto query_uniform_location(const std::string_view& name) const -> GLint;

    void set_uniform(const std::string_view& name, glm::vec3 vec3) const;

    void bind() const;
    void customize(std::function<void(ShaderProgram&)> customizer);
    void free_gpu_resources() noexcept;

private:
    GLuint program_ = 0;
    Shader fragment_shader_;
    Shader vertex_shader_;
};

} // namespace engine

#endif // ENGINE_SHADERPROGRAM_H

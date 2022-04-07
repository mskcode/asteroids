#ifndef OPENGL_SHADERPROGRAM_H
#define OPENGL_SHADERPROGRAM_H

#include "Shader.h"
#include "opengl.h"
#include <string_view>
#include <vector>

namespace opengl {

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

    void bind() const;
    void free_gpu_resources() noexcept;

private:
    GLuint program_ = 0;
    Shader fragment_shader_;
    Shader vertex_shader_;
};

} // namespace opengl

#endif // OPENGL_SHADERPROGRAM_H

#pragma once

#include "OpenGlObject.h"
#include "Resource.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/vec3.hpp"
#include "opengl.h"
#include <functional>
#include <string>
#include <string_view>
#include <vector>

namespace engine {

/**
 * When defining shader attributes you can alternatively use either location,
 * name or both. When both are defined, location has precedence.
 */
struct VertexShaderAttribute {
    GLint location{-1};
    std::string name;
    GLint size{0};
    GLenum type{0};
    bool normalized{false};
    GLuint relative_offset{0};
};

class Shader final {
public:
    Shader() = default;
    Shader(const Shader&) = default;
    Shader(Shader&&) noexcept = default;
    ~Shader() = default;

    auto operator=(const Shader&) -> Shader& = default;
    auto operator=(Shader&& rhs) noexcept -> Shader& = default;

    static auto create(GLenum type, const std::string_view& path, std::vector<VertexShaderAttribute> attributes = {})
        -> Shader;

    [[nodiscard]] auto object() const -> OpenGlObject { return obj_; }
    [[nodiscard]] auto type() const -> GLenum { return type_; }
    [[nodiscard]] auto attributes() const -> const std::vector<VertexShaderAttribute>& { return attributes_; }
    [[nodiscard]] auto is_vertex_shader() const -> bool { return type_ == GL_VERTEX_SHADER; }
    [[nodiscard]] auto is_fragment_shader() const -> bool { return type_ == GL_FRAGMENT_SHADER; }

private:
    Shader(OpenGlObject obj, GLenum type, const std::vector<VertexShaderAttribute>& attributes);

    OpenGlObject obj_;
    GLenum type_{0};
    std::vector<VertexShaderAttribute> attributes_{};
};

class ShaderProgram final {
public:
    ShaderProgram() = default;
    ShaderProgram(const ShaderProgram&) = default;
    ShaderProgram(ShaderProgram&&) noexcept = default;
    ~ShaderProgram() = default;

    auto operator=(const ShaderProgram&) -> ShaderProgram& = default;
    auto operator=(ShaderProgram&&) noexcept -> ShaderProgram& = default;

    static auto create(const std::string& name, const Shader& vertex_shader, const Shader& fragment_shader)
        -> ShaderProgram;

    [[nodiscard]] auto object() const -> OpenGlObject { return obj_; }
    [[nodiscard]] auto name() const -> const std::string& { return name_; }
    [[nodiscard]] auto vertex_shader() const -> const Shader& { return vertex_shader_; }
    [[nodiscard]] auto fragment_shader() const -> const Shader& { return fragment_shader_; }

    [[nodiscard]] auto query_attribute_location(const std::string_view& name) const -> GLint;
    [[nodiscard]] auto query_uniform_location(const std::string_view& name) const -> GLint;

    void set_uniform(const std::string_view& name, glm::vec3 vec3) const;
    void set_uniform(const std::string_view& name, glm::mat4 mat4) const;

    void bind() const;
    void unbind() const;
    void customize(std::function<void(ShaderProgram&)> customizer);

private:
    ShaderProgram(OpenGlObject obj,
                  const std::string& name,
                  const Shader& vertex_shader,
                  const Shader& fragment_shader);

    OpenGlObject obj_;
    std::string name_;
    Shader vertex_shader_;
    Shader fragment_shader_;
};

class ShaderProgramRegistry final {
public:
    ShaderProgramRegistry() = default;
    ShaderProgramRegistry(const ShaderProgramRegistry&) = delete;
    ShaderProgramRegistry(ShaderProgramRegistry&&) noexcept = delete;
    ~ShaderProgramRegistry() = default;

    auto operator=(const ShaderProgramRegistry&) -> ShaderProgramRegistry& = delete;
    auto operator=(ShaderProgramRegistry&&) noexcept -> ShaderProgramRegistry& = delete;

    static auto instance() -> ShaderProgramRegistry&;

    void set(Resource id, const ShaderProgram& shader_program);
    auto get(Resource id) -> ShaderProgram&;

private:
    std::unordered_map<u32, ShaderProgram> shader_program_map_;
};

} // namespace engine

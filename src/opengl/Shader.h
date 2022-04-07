#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "opengl.h"
#include <string>
#include <string_view>
#include <vector>

namespace opengl {

struct VertexShaderAttribute {
    std::string name;
    GLint size;
    GLenum type;
    bool normalized;
    GLuint relative_offset;
};

class Shader final {
public:
    Shader(GLenum type, const std::string_view& path, std::vector<VertexShaderAttribute> attributes = {});
    Shader(const Shader& other) = delete;
    Shader(Shader&& other) noexcept;
    virtual ~Shader();

    auto operator=(const Shader&) -> Shader& = delete;
    auto operator=(Shader&& rhs) noexcept -> Shader&;

    [[nodiscard]] auto id() const -> GLuint;
    [[nodiscard]] auto type() const -> GLenum;
    [[nodiscard]] auto attributes() const -> const std::vector<VertexShaderAttribute>&;
    [[nodiscard]] auto is_vertex_shader() const -> bool;
    [[nodiscard]] auto is_fragment_shader() const -> bool;

    void free_gpu_resources() noexcept;

private:
    GLenum type_ = 0;
    GLuint id_ = 0;
    std::vector<VertexShaderAttribute> attributes_;
};

} // namespace opengl

#endif // OPENGL_SHADER_H

#ifndef OPENGL_SHADERREGISTRY_H
#define OPENGL_SHADERREGISTRY_H

#include "ShaderProgram.h"
#include <vector>

namespace opengl {

class ShaderProgramRegistry final {
public:
    ShaderProgramRegistry();
    ShaderProgramRegistry(const ShaderProgramRegistry&) = delete;
    ShaderProgramRegistry(ShaderProgramRegistry&& other) noexcept;
    ~ShaderProgramRegistry() = default;

    auto operator=(const ShaderProgramRegistry&) -> ShaderProgramRegistry& = delete;
    auto operator=(ShaderProgramRegistry&&) noexcept -> ShaderProgramRegistry&;

    void set(int index, ShaderProgram&& shader);
    [[nodiscard]] auto get(int index) const -> const ShaderProgram&;
    void use(int index);

private:
    std::vector<ShaderProgram> registry_;
    int shader_index_currently_in_use_;
};

} // namespace opengl

#endif // OPENGL_SHADERREGISTRY_H

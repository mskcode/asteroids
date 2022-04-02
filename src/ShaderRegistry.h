#ifndef OPENGL_SHADERREGISTRY_H
#define OPENGL_SHADERREGISTRY_H

#include "ShaderProgram.h"
#include <vector>

namespace opengl {

class ShaderRegistry final {
public:
    ShaderRegistry(const ShaderRegistry&) = delete;
    ShaderRegistry(ShaderRegistry&&) = delete;
    ~ShaderRegistry() = default;

    auto operator=(const ShaderRegistry&) -> ShaderRegistry& = delete;
    auto operator=(ShaderRegistry&&) -> ShaderRegistry& = delete;

    static auto instance() -> ShaderRegistry&;

    void set(int index, ShaderProgram&& shader);
    [[nodiscard]] auto get(int index) const -> const ShaderProgram&;
    void use(int index);

private:
    std::vector<ShaderProgram> registry_;
    int currently_in_use_;

    ShaderRegistry() = default;
};

} // namespace opengl

#endif // OPENGL_SHADERREGISTRY_H

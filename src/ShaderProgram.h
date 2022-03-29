#ifndef OPENGL_SHADERPROGRAM_H
#define OPENGL_SHADERPROGRAM_H

#include "opengl.h"
#include <vector>
#include "Shader.h"

namespace opengl {

class ShaderProgram final {
public:
    ShaderProgram();

    ~ShaderProgram();

    void attach_shader(Shader shader);

    void attach_shaders(const std::vector<Shader> &shaders);

    void link();

    GLuint id() const;

private:
    GLuint program_;
};

} // namespace

#endif // OPENGL_SHADERPROGRAM_H

#ifndef OPENGL_SHADERPROGRAM_H
#define OPENGL_SHADERPROGRAM_H

#include "opengl.h"

namespace opengl {

class ShaderProgram final {
public:
    ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;

    ~ShaderProgram();

    ShaderProgram& operator=(const ShaderProgram&) = delete;

    void load_shader_file(GLenum shader_type, const char* path) const;

    void load_shader_string(GLenum shader_type, const char* str) const;

    void link() const;

    GLuint id() const;

private:
    GLuint program_;
};

} // namespace opengl

#endif // OPENGL_SHADERPROGRAM_H

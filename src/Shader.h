#ifndef OPENGL_SHADER_H
#define OPENGL_SHADER_H

#include "opengl.h"

namespace opengl {

class Shader final {
public:
    static Shader load_string(GLenum shader_type, const char *str);

    static Shader load_file(GLenum shader_type, const char *path);

    ~Shader();

    GLuint id() const;

private:
    GLuint shader_;

    Shader(GLenum shader_type, const char *shader_source);
};

} // namespace

#endif // OPENGL_SHADER_H

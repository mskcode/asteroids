#ifndef OPENGL_VERTEX_H
#define OPENGL_VERTEX_H

#include "opengl.h"

namespace opengl {

class Vertex {
public:
    Vertex();

    ~Vertex();

    void draw();

private:
    GLuint vertex_array_object_;
    GLuint vertex_buffer_object_;

    GLfloat vertices_[9] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };
};

} // namespace

#endif // OPENGL_VERTEX_H

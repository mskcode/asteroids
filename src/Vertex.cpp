#include "Vertex.h"

using namespace opengl;

Vertex::Vertex() {
    glCreateBuffers(1, &vertex_buffer_object_);
    glNamedBufferStorage(vertex_buffer_object_, sizeof(vertices_), vertices_, GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &vertex_array_object_);

    GLuint vertex_array_binding_point = 0;  // A binding point in VAO. See GL_MAX_VERTEX_ATTRIB_BINDINGS
    glVertexArrayVertexBuffer(
            vertex_array_object_,        // vao to bind
            vertex_array_binding_point,     // Could be 1, 2... if there were several vbo to source.
            vertex_buffer_object_,       // VBO to bound at "vertex_array_binding_point".
            0,                   // offset of the first element in the buffer hctVBO.
            3 * sizeof(float));  // stride == 3 position floats + 3 color floats.

    GLuint attribute_position = 0;
    GLuint attribute_column = 1;

    glEnableVertexArrayAttrib(vertex_array_object_, attribute_position);
    glEnableVertexArrayAttrib(vertex_array_object_, attribute_column);

    glVertexArrayAttribFormat(vertex_array_object_, attribute_position, 3, GL_FLOAT, false, 0);
    glVertexArrayAttribFormat(vertex_array_object_, attribute_column, 3, GL_FLOAT, false, 3 * sizeof(float));

    glVertexArrayAttribBinding(vertex_array_object_, attribute_position, vertex_array_binding_point);
    glVertexArrayAttribBinding(vertex_array_object_, attribute_column, vertex_array_binding_point);
}

Vertex::~Vertex() {

}

void Vertex::bind() {
    glBindVertexArray(vertex_array_object_);
}

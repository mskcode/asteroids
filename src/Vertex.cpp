#include "Vertex.h"

using namespace opengl;

Vertex::Vertex() {
    shader_program_ = new ShaderProgram();
    shader_program_->load_shader_file(GL_VERTEX_SHADER, "./resources/shaders/vertex.vert");
    shader_program_->load_shader_file(GL_FRAGMENT_SHADER, "./resources/shaders/fragment.frag");
    shader_program_->link();

    glCreateBuffers(1, &vertex_buffer_object_);
    glNamedBufferStorage(vertex_buffer_object_, sizeof(vertices_), vertices_, GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &vertex_array_object_);

    GLuint vertex_array_binding_point = 0;
    glVertexArrayVertexBuffer(vertex_array_object_,
                              vertex_array_binding_point,
                              vertex_buffer_object_,
                              0,
                              3 * sizeof(float));

    auto attribute_1 = glGetAttribLocation(shader_program_->id(), "aPos");
    glEnableVertexArrayAttrib(vertex_array_object_, attribute_1);
    glVertexArrayAttribFormat(vertex_array_object_, attribute_1, 3, GL_FLOAT, false, 0);
    glVertexArrayAttribBinding(vertex_array_object_, attribute_1, vertex_array_binding_point);
}

Vertex::~Vertex() {
    GLuint arrays[] = {vertex_array_object_};
    glDeleteVertexArrays(1, arrays);

    GLuint buffers[] = {vertex_buffer_object_};
    glDeleteBuffers(1, buffers);

    delete shader_program_;
}

void Vertex::draw() {
    glUseProgram(shader_program_->id());
    glBindVertexArray(vertex_array_object_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0); // unbind
}

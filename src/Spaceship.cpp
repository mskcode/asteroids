#include "Spaceship.h"
#include "linmath/linmath.h"

using namespace asteroids;

static const struct {
    float x, y;
    float r, g, b;
} vertices[3] = {
        {-0.6f, -0.4f, 1.f, 0.f, 0.f},
        {0.6f,  -0.4f, 0.f, 1.f, 0.f},
        {0.f,   0.6f,  0.f, 0.f, 1.f}
};

Spaceship::Spaceship() {
    initialize_shaders();
    initialize_objects();
}

void Spaceship::initialize_objects() {
    glCreateBuffers(1, &vertex_buffer_object_);
    glNamedBufferStorage(vertex_buffer_object_, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);

    glCreateVertexArrays(1, &vertex_array_object_);

    GLuint vertex_array_binding_point = 0;  // A binding point in VAO. See GL_MAX_VERTEX_ATTRIB_BINDINGS
    glVertexArrayVertexBuffer(
            vertex_array_object_,        // vao to bind
            vertex_array_binding_point,     // Could be 1, 2... if there were several vbo to source.
            vertex_buffer_object_,       // VBO to bound at "vertex_array_binding_point".
            0,                   // offset of the first element in the buffer hctVBO.
            6 * sizeof(float));  // stride == 3 position floats + 3 color floats.

    glEnableVertexArrayAttrib(vertex_array_object_, vpos_location_);
    glEnableVertexArrayAttrib(vertex_array_object_, vcol_location_);

    glVertexArrayAttribFormat(vertex_array_object_, vpos_location_, 3, GL_FLOAT, false, 0);
    glVertexArrayAttribFormat(vertex_array_object_, vcol_location_, 3, GL_FLOAT, false, 3 * sizeof(float));

    glVertexArrayAttribBinding(vertex_array_object_, vpos_location_, vertex_array_binding_point);
    glVertexArrayAttribBinding(vertex_array_object_, vcol_location_, vertex_array_binding_point);
}

static const char *vertex_shader_text =
        "#version 110\n"
        "uniform mat4 MVP;\n"
        "attribute vec3 vCol;\n"
        "attribute vec2 vPos;\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
        "    color = vCol;\n"
        "}\n";

static const char *fragment_shader_text =
        "#version 110\n"
        "varying vec3 color;\n"
        "void main()\n"
        "{\n"
        "    gl_FragColor = vec4(color, 1.0);\n"
        "}\n";

void Spaceship::initialize_shaders() {
    vertex_shader_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_, 1, &vertex_shader_text, nullptr);
    glCompileShader(vertex_shader_);

    fragment_shader_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_, 1, &fragment_shader_text, nullptr);
    glCompileShader(fragment_shader_);

    program_ = glCreateProgram();
    glAttachShader(program_, vertex_shader_);
    glAttachShader(program_, fragment_shader_);
    glLinkProgram(program_);

    mvp_location_ = glGetUniformLocation(program_, "MVP");
    vpos_location_ = glGetAttribLocation(program_, "vPos");
    vcol_location_ = glGetAttribLocation(program_, "vCol");

    //glUseProgram(program_);
}

void Spaceship::render(GLFWwindow *window) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float) height;

    mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    glUseProgram(program_);
    glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, (const GLfloat *) mvp);
    glBindVertexArray(vertex_array_object_);
}

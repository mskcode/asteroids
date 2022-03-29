#include "Spaceship.h"

#include <vector>
#include "linmath/linmath.h"

using namespace asteroids;

Spaceship::Spaceship() {
    shader_program_ = new opengl::ShaderProgram();
    vertex_ = new opengl::Vertex();
    initialize_shaders();
}

Spaceship::~Spaceship() {
    delete vertex_;
    delete shader_program_;
}

static const char *vertex_shader_text =
        "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n";

static const char *fragment_shader_text =
        "#version 460 core\n"
        "out vec4 FragColor;\n"
        "\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n";

void Spaceship::initialize_shaders() {
    auto vertex_shader = opengl::Shader::load_string(GL_VERTEX_SHADER, vertex_shader_text);
    auto fragment_shader = opengl::Shader::load_string(GL_FRAGMENT_SHADER, fragment_shader_text);

    shader_program_->attach_shaders({vertex_shader, fragment_shader});
    shader_program_->link();
}

void Spaceship::render([[maybe_unused]] GLFWwindow *window) {
    //int width, height;
    //glfwGetFramebufferSize(window, &width, &height);
    //float ratio = width / (float) height;

    glUseProgram(shader_program_->id());
    vertex_->draw();

    /* mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m); */


    //glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, (const GLfloat *) mvp);
}

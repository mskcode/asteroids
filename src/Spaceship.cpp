#include "Spaceship.h"

#include <vector>
#include "linmath/linmath.h"

using namespace asteroids;

Spaceship::Spaceship() {
    vertex_ = new opengl::Vertex();
}

Spaceship::~Spaceship() {
    delete vertex_;
}

void Spaceship::render([[maybe_unused]] GLFWwindow *window) {
    //int width, height;
    //glfwGetFramebufferSize(window, &width, &height);
    //float ratio = width / (float) height;

    vertex_->draw();

    /* mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m); */


    //glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, (const GLfloat *) mvp);
}

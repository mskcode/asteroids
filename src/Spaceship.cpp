#include "Spaceship.h"
#include "linmath/linmath.h"
#include <vector>

using namespace asteroids;

Spaceship::Spaceship() : renderable_object_(0) {
    renderable_object_.update_data({{{{-0.5F, -0.5F, 0.0F}, {1.f, 0.f, 0.f}},
                                     {{0.5F, -0.5F, 0.0F}, {0.f, 1.f, 0.f}},
                                     {{0.0F, 0.5F, 0.0F}, {0.f, 0.f, 1.f}}}});
}

void Spaceship::render([[maybe_unused]] GLFWwindow* window) {
    renderable_object_.render();

    /* mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m); */

    // glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, (const GLfloat *) mvp);
}

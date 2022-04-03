#include "Spaceship.h"
#include <array>

using namespace asteroids;

static auto generate_vertex_data(const Coordinates3D& position) -> std::array<opengl::Vertex3D, 3> {
    constexpr opengl::VertexColor color{0.5f, 0.1f, 0.5f};
    return {{{{position.x - 0.2f, position.y - 0.2f, 0.0f}, color}, // bottom left
             {{position.x + 0.2f, position.y - 0.2f, 0.0f}, color}, // bottom right
             {{position.x, position.y + 0.2f, 0.0F}, color}}};      // top
}

Spaceship::Spaceship(const opengl::ShaderProgramRegistry& spr) :
    renderable_object_(spr, 0),
    position_({0.0f, 0.0f, 0.0f}) {
    renderable_object_.update_data(generate_vertex_data(position_));
}

void Spaceship::render(opengl::ShaderProgramRegistry& spr) {
    renderable_object_.render(spr);
}

void Spaceship::move(float x_displacement, float y_displacement) {
    position_.x += x_displacement;
    position_.y += y_displacement;
    renderable_object_.update_data(generate_vertex_data(position_));
}

/*
    mat4x4 m, p, mvp;
    mat4x4_identity(m);
    mat4x4_rotate_Z(m, m, (float) glfwGetTime());
    mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
    mat4x4_mul(mvp, p, m);

    glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, (const GLfloat *) mvp);
*/

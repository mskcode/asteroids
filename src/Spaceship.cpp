#include "Spaceship.h"
#include "common/debug.h"
#include "opengl/KeyEventDispatcher.h"
#include <array>

using namespace asteroids;

static auto generate_vertex_data(const Coordinates3D& position) -> std::array<opengl::Vertex3D, 3> {
    constexpr opengl::VertexColor color{0.5f, 0.1f, 0.5f};
    return {{{{position.x - 0.2f, position.y - 0.2f, 0.0f}, color}, // bottom left
             {{position.x + 0.2f, position.y - 0.2f, 0.0f}, color}, // bottom right
             {{position.x, position.y + 0.2f, 0.0F}, color}}};      // top
}

Spaceship::Spaceship(opengl::RenderableObject<opengl::Vertex3D, 3>&& renderable_object,
                     const opengl::KeyEventDispatcher& key_event_dispatcher) :
    renderable_object_(std::move(renderable_object)),
    keyboard_(key_event_dispatcher.keyboard()),
    position_({0.0f, 0.0f, 0.0f}) {

    renderable_object_.update_data(generate_vertex_data(position_));
}

void Spaceship::update() {
    if (keyboard_[GLFW_KEY_UP].is_down()) {
        this->move(0, 0.1f);
    }
    if (keyboard_[GLFW_KEY_DOWN].is_down()) {
        this->move(0, -0.1f);
    }
    if (keyboard_[GLFW_KEY_LEFT].is_down()) {
        this->move(-0.1f, 0);
    }
    if (keyboard_[GLFW_KEY_RIGHT].is_down()) {
        this->move(0.1f, 0);
    }
}

void Spaceship::render() {
    renderable_object_.render();
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

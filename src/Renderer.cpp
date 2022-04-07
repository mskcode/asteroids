#include "Renderer.h"

using namespace asteroids;

Renderer::Renderer(const opengl::Window& window) :
    window_(window) {}

void Renderer::render() {
    int width;
    int height;
    glfwGetFramebufferSize(window_.window_pointer(), &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto* renderable : renderables_) {
        renderable->render();
    }

    ++frame_counter_;
}

void Renderer::add_renderable(Renderable* renderable) {
    renderables_.push_back(renderable);
}

void Renderer::toggle_wireframe_rendering() {
    if (wireframe_rendering_) {
        // normal rendering
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        wireframe_rendering_ = false;
    } else {
        // wireframe rendering
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        wireframe_rendering_ = true;
    }
}

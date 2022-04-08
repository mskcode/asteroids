#include "Renderer.h"

using namespace game;

Renderer::Renderer(const engine::Window& window, const GameObjectFactory& game_object_factory) :
    window_(window),
    game_object_factory_(game_object_factory) {}

void Renderer::render() {
    int width;
    int height;
    glfwGetFramebufferSize(window_.window_pointer(), &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (auto* renderable : game_object_factory_.renderables()) {
        renderable->render();
    }

    ++frame_counter_;
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

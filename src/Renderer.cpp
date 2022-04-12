#include "Renderer.h"

using namespace game;
using namespace engine;

Renderer::Renderer(const Window& window,
                   const GameObjectFactory& game_object_factory,
                   RenderableText& renderable_text) :
    window_(window),
    game_object_factory_(game_object_factory),
    renderable_text_(renderable_text) {}

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

    renderable_text_.set_text("Test FOO", -0.5f, 0.5f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
    renderable_text_.render();

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

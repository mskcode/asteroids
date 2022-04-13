#include "Renderer.h"

using namespace game;
using namespace engine;

Renderer::Renderer(const Window& window, const GameObjectFactory& game_object_factory, TextRenderer& renderable_text) :
    window_(window),
    game_object_factory_(game_object_factory),
    renderable_text_(renderable_text) {

    // enable polygon culling; this doesn't specify which polygons should be
    // culled, only enables it:
    // https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glCullFace.xml
    glEnable(GL_CULL_FACE);

    // enable pixel blending and configure the blend function; according to
    // OpenGL documentation, transparency is best achieved using blend function
    // (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA):
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBlendFunc.xhtml
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

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

    renderable_text_.draw_text("Test FOO", 100.0f, 100.0f, 0.5f);

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

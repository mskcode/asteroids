#include "Renderer.h"
#include "common/strutils.h"
#include "common/timeutils.h"
#include <cinttypes>

using namespace game;
using namespace engine;

Renderer::Renderer(const Window& window,
                   Camera& camera,
                   const GameObjectFactory& game_object_factory,
                   TextRenderer& renderable_text) :
    window_(window),
    camera_(camera),
    game_object_factory_(game_object_factory),
    renderable_text_(renderable_text) {

    // enable pixel blending and configure the blend function; according to
    // OpenGL documentation, transparency is best achieved using blend function
    // (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA):
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBlendFunc.xhtml
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // enable depth testing:
    // https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glDepthFunc.xhtml
    //
    // remember to glClear(... | GL_DEPTH_BUFFER_BIT) when doing this
    glEnable(GL_DEPTH_TEST);
}

void Renderer::render() {
    using namespace common;
    auto sw = time::StopWatch::start();

    // ======================================================================
    // prepare for new render cycle
    // ======================================================================

    int width;
    int height;
    glfwGetFramebufferSize(window_.window_pointer(), &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ======================================================================
    // render models
    // ======================================================================

    // enable polygon culling; this doesn't specify which polygons should be
    // culled, only enables it:
    // https://www.khronos.org/registry/OpenGL-Refpages/es2.0/xhtml/glCullFace.xml
    //
    // NOTICE the default culling mode GL_BACK ended up rendering our cube so
    //   that we could see inside it
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    if (wireframe_rendering_) {
        // wireframe rendering
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        // normal rendering
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    camera_.update_shader_matrix();

    for (auto* renderable : game_object_factory_.renderables()) {
        renderable->render();
    }

    // ======================================================================
    // render text
    // ======================================================================

    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    auto text = str::format("RT AVG %" PRIu64 " us", duration_histogram_.avg().value(time::TimeUnit::MICROSECONDS));
    renderable_text_.draw_text(text, 100.0f, 100.0f, 0.5f);

    auto text2 = str::format("FPS %.0f", fps_counter_.hertz());
    renderable_text_.draw_text(text2, 100.0f, 120.0f, 0.5f);

    duration_histogram_.sample(sw.split());
    fps_counter_.inc();

    glfwSwapBuffers(window_.window_pointer());
}

void Renderer::toggle_wireframe_rendering() {
    wireframe_rendering_ = !wireframe_rendering_;
}

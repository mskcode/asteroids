#ifndef GAME_RENDERER_H
#define GAME_RENDERER_H

#include "GameObjectFactory.h"
#include "Renderable.h"
#include "common/timeutils.h"
#include "engine/TextRenderer.h"
#include "engine/Window.h"
#include "engine/opengl.h"
#include <cstdint>
#include <vector>

namespace game {

class Renderer final {
public:
    Renderer(const engine::Window& window,
             const GameObjectFactory& game_object_factory,
             engine::TextRenderer& renderable_text);
    ~Renderer() = default;

    void render();
    void toggle_wireframe_rendering();

private:
    const engine::Window& window_;
    const GameObjectFactory& game_object_factory_;
    uint64_t frame_counter_{0};
    bool wireframe_rendering_{false};
    engine::TextRenderer& renderable_text_;
    common::time::DurationHistogram<> duration_histogram_;
};

} // namespace game

#endif // GAME_RENDERER_H

#ifndef ASTEROIDS_RENDERER_H
#define ASTEROIDS_RENDERER_H

#include "Renderable.h"
#include "opengl/Window.h"
#include "opengl/opengl.h"
#include <cstdint>
#include <vector>

namespace asteroids {

class Renderer final {
public:
    Renderer(const opengl::Window& window);
    ~Renderer() = default;

    void add_renderable(Renderable* renderable);
    void render();
    void toggle_wireframe_rendering();

private:
    const opengl::Window& window_;
    std::vector<Renderable*> renderables_;
    uint64_t frame_counter_ = 0;
    bool wireframe_rendering_ = false;
};

} // namespace asteroids

#endif // ASTEROIDS_RENDERER_H

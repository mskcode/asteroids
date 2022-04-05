#ifndef ASTEROIDS_RENDERER_H
#define ASTEROIDS_RENDERER_H

#include "Renderable.h"
#include "opengl/Window.h"
#include "opengl/opengl.h"
#include <vector>

namespace asteroids {

class Renderer final {
public:
    Renderer(const opengl::Window& window);
    ~Renderer() = default;

    void add_renderable(Renderable* renderable);
    void render();

private:
    const opengl::Window& window_;
    std::vector<Renderable*> renderables_;
};

} // namespace asteroids

#endif // ASTEROIDS_RENDERER_H

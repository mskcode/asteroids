#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include "Renderable.h"
#include "RenderableObject.h"
#include "ShaderProgram.h"
#include "opengl.h"

namespace asteroids {

class Spaceship final : public Renderable {
public:
    Spaceship();
    ~Spaceship() = default;

    void render(GLFWwindow* window) override;

private:
    opengl::RenderableObject<opengl::Vertex3D, 3> renderable_object_;
};

} // namespace asteroids

#endif // ASTEROIDS_SPACESHIP_H

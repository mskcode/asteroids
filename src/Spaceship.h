#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include "opengl.h"
#include "Renderable.h"
#include "ShaderProgram.h"
#include "Vertex.h"

namespace asteroids {

class Spaceship final : public Renderable {
public:
    Spaceship();

    ~Spaceship();

    void render(GLFWwindow *window) override;

private:
    opengl::Vertex *vertex_;
};

} // namespace

#endif //ASTEROIDS_SPACESHIP_H

#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include "RenderableObject.h"
#include "ShaderProgram.h"
#include "opengl.h"

namespace asteroids {

struct Coordinates3D final {
    float x;
    float y;
    float z;
};

class Spaceship final {
public:
    Spaceship(const opengl::ShaderProgramRegistry& spr);
    ~Spaceship() = default;

    void render(opengl::ShaderProgramRegistry& spr);
    void move(float x_displacement, float y_displacement);

private:
    opengl::RenderableObject<opengl::Vertex3D, 3> renderable_object_;
    Coordinates3D position_;
};

} // namespace asteroids

#endif // ASTEROIDS_SPACESHIP_H

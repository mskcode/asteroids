#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include "Renderable.h"
#include "opengl/RenderableObject.h"
#include "opengl/ShaderProgram.h"
#include "opengl/opengl.h"

namespace asteroids {

struct Coordinates3D final {
    float x;
    float y;
    float z;
};

class Spaceship final : public Renderable {
public:
    Spaceship();
    ~Spaceship() = default;

    void render() override;
    void move(float x_displacement, float y_displacement);

private:
    opengl::RenderableObject<opengl::Vertex3D, 3> renderable_object_;
    Coordinates3D position_;
};

} // namespace asteroids

#endif // ASTEROIDS_SPACESHIP_H

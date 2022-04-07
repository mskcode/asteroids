#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include "Renderable.h"
#include "Updateable.h"
#include "opengl/KeyEventDispatcher.h"
#include "opengl/RenderableObject.h"
#include "opengl/ShaderProgram.h"
#include "opengl/opengl.h"

namespace asteroids {

struct Coordinates3D final {
    float x;
    float y;
    float z;
};

class Spaceship final : public Renderable, Updateable {
public:
    Spaceship(opengl::RenderableObject<opengl::Vertex3D, 3>&& renderable_object,
              const opengl::KeyEventDispatcher& key_event_dispatcher);
    ~Spaceship() = default;

    void update() override;
    void render() override;

    void move(float x_displacement, float y_displacement);

private:
    opengl::RenderableObject<opengl::Vertex3D, 3> renderable_object_;
    const opengl::Keyboard& keyboard_;
    Coordinates3D position_;
};

} // namespace asteroids

#endif // ASTEROIDS_SPACESHIP_H

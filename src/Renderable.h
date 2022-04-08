#ifndef ASTEROIDS_RENDERABLE_H
#define ASTEROIDS_RENDERABLE_H

namespace asteroids {

class Renderable {
public:
    virtual void render() const = 0;
};

} // namespace asteroids

#endif // ASTEROIDS_RENDERABLE_H

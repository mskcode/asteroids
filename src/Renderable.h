#ifndef ASTEROIDS_RENDERABLE_H
#define ASTEROIDS_RENDERABLE_H

#include "glincludes.h"

namespace asteroids {

class Renderable {
public:
    virtual void render(GLFWwindow *window) = 0;
};

} // namespace

#endif //ASTEROIDS_RENDERABLE_H

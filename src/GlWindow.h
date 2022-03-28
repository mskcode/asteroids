#ifndef ASTEROIDS_GLWINDOW_H
#define ASTEROIDS_GLWINDOW_H

#include "glincludes.h"

namespace asteroids {

class GlWindow final {
public:
    GlWindow(int width, int height);

    ~GlWindow();

    void run();

    void close();

private:
    GLFWwindow *window = nullptr;
};

} // namespace

#endif //ASTEROIDS_GLWINDOW_H

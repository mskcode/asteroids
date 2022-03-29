#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "opengl.h"

namespace opengl {

class Window final {
public:
    Window(int width, int height);

    ~Window();

    void run();

    void close();

private:
    GLFWwindow *window = nullptr;
};

} // namespace

#endif // OPENGL_WINDOW_H

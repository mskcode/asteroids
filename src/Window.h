#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "opengl.h"

namespace opengl {

class Window final {
public:
    Window(int width, int height);

    Window(const Window&) = delete;
    Window(const Window&&) = delete;

    ~Window();

    Window& operator=(const Window&) = delete;
    Window& operator=(const Window&&) = delete;

    void run();

    void close();

private:
    GLFWwindow* window_ = nullptr;
    bool terminated_ = false;
};

} // namespace opengl

#endif // OPENGL_WINDOW_H

#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "opengl.h"
#include <functional>

namespace opengl {

class Window final {
public:
    Window(int width, int height);

    Window(const Window&) = delete;
    Window(const Window&&) = delete;

    ~Window();

    auto operator=(const Window&) -> Window& = delete;
    auto operator=(const Window&&) -> Window& = delete;

    void run(const std::function<bool(GLFWwindow*)>& render);

    void close();

private:
    GLFWwindow* window_ = nullptr;
    bool terminated_ = false;
};

} // namespace opengl

#endif // OPENGL_WINDOW_H

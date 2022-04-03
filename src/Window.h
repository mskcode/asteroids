#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "KeyEvent.h"
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
    void on_key_event(const std::function<void(const KeyEvent& event)>& key_event_handler);
    void toggle_wireframe_rendering();

private:
    GLFWwindow* window_ = nullptr;
    bool terminated_ = false;
    bool wireframe_rendering_ = false;
};

} // namespace opengl

#endif // OPENGL_WINDOW_H

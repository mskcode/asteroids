#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include "KeyEvent.h"
#include "opengl.h"
#include <functional>
#include <string_view>

namespace opengl {

class Window final {
public:
    Window(const std::string_view& title, int width, int height, bool vsync_enabled = true);
    Window(const Window&) = delete;
    Window(const Window&&) = delete;
    ~Window();

    auto operator=(const Window&) -> Window& = delete;
    auto operator=(const Window&&) noexcept -> Window& = delete;

    [[nodiscard]] auto should_close() const -> bool;
    [[nodiscard]] auto window_pointer() const -> GLFWwindow*;

    void run(const std::function<bool(GLFWwindow*)>& render);
    void close();

private:
    GLFWwindow* window_ = nullptr;
    bool wireframe_rendering_ = false;
};

} // namespace opengl

#endif // OPENGL_WINDOW_H

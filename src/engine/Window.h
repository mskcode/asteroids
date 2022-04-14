#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include "KeyEvent.h"
#include "opengl.h"
#include "types.h"
#include <functional>
#include <string>
#include <string_view>

namespace engine {

struct WindowOptions final {
    std::string title{"GLFW Window"};
    Dimensions2D window_size{.width = 800, .height = 600};
    bool vsync_enabled{true};
    bool resizable{true};
    int opengl_version_major{4};
    int opengl_version_minor{6};
};

class Window final {
public:
    Window(const WindowOptions& options);
    Window(const Window&) = delete;
    Window(Window&&) = delete;
    ~Window();

    auto operator=(const Window&) -> Window& = delete;
    auto operator=(const Window&&) noexcept -> Window& = delete;

    [[nodiscard]] auto should_close() const -> bool;
    [[nodiscard]] auto window_pointer() const -> GLFWwindow*;
    [[nodiscard]] auto window_size() const -> const Dimensions2D&;

    void close();
    void update_window_size();

private:
    GLFWwindow* window_{nullptr};
    Dimensions2D window_size_{};
};

} // namespace engine

#endif // ENGINE_WINDOW_H

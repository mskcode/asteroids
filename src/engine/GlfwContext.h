#ifndef ENGINE_GLFWCONTEXT_H
#define ENGINE_GLFWCONTEXT_H

namespace engine {

class GlfwContext final {
public:
    GlfwContext();
    GlfwContext(const GlfwContext&) = delete;
    GlfwContext(GlfwContext&&) = delete;
    ~GlfwContext();

    auto operator=(const GlfwContext&) -> GlfwContext& = delete;
    auto operator=(GlfwContext&&) -> GlfwContext& = delete;

private:
    bool terminated_ = false;
};

} // namespace engine

#endif // ENGINE_GLFWCONTEXT_H

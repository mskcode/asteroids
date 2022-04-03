#ifndef OPENGL_GLFWCONTEXT_H
#define OPENGL_GLFWCONTEXT_H

namespace opengl {

class GlfwContext final {
public:
    GlfwContext();
    GlfwContext(const GlfwContext&) = delete;
    GlfwContext(GlfwContext&&) = delete;
    ~GlfwContext();

    auto operator=(const GlfwContext&) -> GlfwContext& = delete;
    auto operator=(GlfwContext&&) -> GlfwContext& = delete;

private:
    bool terminated_;
};

} // namespace opengl

#endif // OPENGL_GLFWCONTEXT_H

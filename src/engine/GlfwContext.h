#pragma once

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

#ifndef ENGINE_CAMERADIRECTOR_H
#define ENGINE_CAMERADIRECTOR_H

#include <glm/vec3.hpp>

namespace engine {

class CameraDirector {
public:
    virtual ~CameraDirector() = default;

    virtual void update() = 0;

    [[nodiscard]] virtual auto front() const -> glm::vec3 = 0;
    [[nodiscard]] virtual auto right() const -> glm::vec3 = 0;
    [[nodiscard]] virtual auto up() const -> glm::vec3 = 0;
    [[nodiscard]] virtual auto position() const -> glm::vec3 = 0;

};

} // namespace engine

#endif // ENGINE_CAMERADIRECTOR_H

#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace engine {

struct Point2D final {
    uint32_t x{0};
    uint32_t y{0};
};

struct Dimensions2D final {
    uint32_t width{0};
    uint32_t height{0};
};

struct Rectangle final {
    Point2D point;
    Dimensions2D dimensions;
};

struct Color final {
    float r{0};
    float g{0};
    float b{0};
    float a{0};

    [[nodiscard]] auto red() const -> float { return r; }
    [[nodiscard]] auto green() const -> float { return g; }
    [[nodiscard]] auto blue() const -> float { return b; }
    [[nodiscard]] auto alpha() const -> float { return a; }
    [[nodiscard]] auto to_vec3() const -> glm::vec3 { return {r, g, b}; }
    [[nodiscard]] auto to_vec4() const -> glm::vec4 { return {r, g, b, a}; }
};

class Colors final {
public:
    static constexpr Color NeonGreen{0.5f, 0.8f, 0.2f};
};

} // namespace engine

#endif // ENGINE_TYPES_H

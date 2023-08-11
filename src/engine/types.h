#pragma once

#include "opengl.h"
#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace engine {

struct Point2D final {
    int32_t x{0};
    int32_t y{0};
};

struct Point2DF final {
    float x{0};
    float y{0};
};

struct Point2DD final {
    double x{0};
    double y{0};
};

struct Point2DL final {
    int64_t x{0};
    int64_t y{0};
};

struct Dimensions2D final {
    int32_t width{0};
    int32_t height{0};
};

struct Rectangle final {
    Point2D point;
    Dimensions2D dimensions;
};

struct Color final {
    GLfloat r{0};
    GLfloat g{0};
    GLfloat b{0};
    GLfloat a{1};

    [[nodiscard]] auto red() const -> GLfloat { return r; }
    [[nodiscard]] auto green() const -> GLfloat { return g; }
    [[nodiscard]] auto blue() const -> GLfloat { return b; }
    [[nodiscard]] auto alpha() const -> GLfloat { return a; }
    [[nodiscard]] auto to_vec3() const -> glm::vec3 { return {r, g, b}; }
    [[nodiscard]] auto to_vec4() const -> glm::vec4 { return {r, g, b, a}; }
};

class Colors final {
public:
    static constexpr Color NeonGreen{0.5f, 0.8f, 0.2f};
};

struct Point3DF {
    GLfloat x{0};
    GLfloat y{0};
    GLfloat z{0};
};

struct TextureCoordinates final {
    GLfloat s{0};
    GLfloat t{0};
};

struct Vertex {
    Point3DF point;
    Color color;
    TextureCoordinates texture_coordinates;
};

} // namespace engine

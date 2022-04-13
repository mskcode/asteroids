#ifndef ENGINE_TEXTRENDERER_H
#define ENGINE_TEXTRENDERER_H

#include "../common/debug.h"
#include "FontBitmapCache.h"
#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "opengl.h"
#include "types.h"
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

namespace engine {

class TextRenderer final {
public:
    TextRenderer(const FontBitmapCache& font_bitmap_cache, const ShaderProgram& shader_program);
    ~TextRenderer() = default;

    void set_color(Color color);
    void draw_text(const std::string& text, float x, float y, float scale = 1.0f);

private:
    const FontBitmapCache& font_bitmap_cache_;
    VertexArrayObject vao_;
    VertexBufferObject vbo_;
};

} // namespace engine

#endif // ENGINE_TEXTRENDERER_H

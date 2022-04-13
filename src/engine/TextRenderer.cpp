#include "TextRenderer.h"

using namespace engine;

struct TextureCoordinates {
    GLfloat position_x = 0; // screen vertex X
    GLfloat position_y = 0; // screen vertex Y
    GLfloat texture_x = 0;  // texture vertex X
    GLfloat texture_y = 0;  // texture vertex Y
};

TextRenderer::TextRenderer(const FontBitmapCache& font_bitmap_cache, const ShaderProgram& shader_program) :
    font_bitmap_cache_(font_bitmap_cache) {
    vao_ = VertexArrayObject::create(&shader_program);
    vbo_ = vao_.create_vbo(1024, sizeof(TextureCoordinates), GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
    this->set_color(Colors::NeonGreen);
}

void TextRenderer::set_color(Color color) {
    auto& shader = vao_.shader_program();
    glUseProgram(shader.id());
    shader.set_uniform("texture_color", color.to_vec3());
}

void TextRenderer::draw_text(const std::string& text, float x, float y, float scale) {
    vao_.bind();

    auto current_x = x;
    for (size_t ix = 0; ix < text.size(); ++ix) {
        auto& character_bitmap = font_bitmap_cache_[text[ix]];

        float xpos = current_x + character_bitmap.bearing().x * scale;
        float ypos = y - (character_bitmap.size().y - character_bitmap.bearing().y) * scale;

        float w = character_bitmap.size().x * scale;
        float h = character_bitmap.size().y * scale;

        std::array<TextureCoordinates, 6> vertices{{{xpos, ypos + h, 0.0f, 0.0f},
                                                    {xpos, ypos, 0.0f, 1.0f},
                                                    {xpos + w, ypos, 1.0f, 1.0f},
                                                    {xpos, ypos + h, 0.0f, 0.0f},
                                                    {xpos + w, ypos, 1.0f, 1.0f},
                                                    {xpos + w, ypos + h, 1.0f, 0.0f}}};

        // bind the texture to given unit and activate it; this is used in
        // the glyph.frag shader
        glBindTextureUnit(0, character_bitmap.texture_id());

        // store the vertex data to VBO and render the triangles
        vbo_.set_data(vertices);
        glDrawArrays(GL_TRIANGLES, 0, vbo_.element_count());

        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th
        // pixels by 64 to get amount of pixels))
        current_x += (character_bitmap.advance_offset_x() >> 6) * scale;
    }

    glBindTextureUnit(0, 0); // unbind texture
    vao_.unbind();
}

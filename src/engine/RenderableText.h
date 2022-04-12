#ifndef ENGINE_RENDERABLETEXT_H
#define ENGINE_RENDERABLETEXT_H

#include "../common/debug.h"
#include "FontBitmapCache.h"
#include "ShaderProgram.h"
#include "opengl.h"
#include <glm/vec3.hpp>
#include <iostream>
#include <string>

namespace engine {

struct TextureCoordinates {
    GLfloat position_x = 0; // screen vertex X
    GLfloat position_y = 0; // screen vertex Y
    GLfloat texture_x = 0;  // texture vertex X
    GLfloat texture_y = 0;  // texture vertex Y
};

class RenderableText final {
public:
    RenderableText(const FontBitmapCache& font_bitmap_cache, const ShaderProgram& shader_program) :
        font_bitmap_cache_(font_bitmap_cache),
        shader_program_id_(shader_program.id()) {
        dbgln("Creating RenderableText object");
        glCreateBuffers(1, &vbo_);
        glNamedBufferStorage(vbo_, g_buffer_size, nullptr, GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
        dbgfln("Created VBO ID %d with size %ld", vbo_, g_buffer_size);

        glCreateVertexArrays(1, &vao_);
        dbgfln("Created VAO ID %d", vao_);

        // bind Vertex Buffer Object (VBO) to Vertex Array Object (VAO) index N
        constexpr GLuint vertex_array_binding_point = 0;
        glVertexArrayVertexBuffer(vao_, vertex_array_binding_point, vbo_, /*offset*/ 0, sizeof(TextureCoordinates));

        // bind shader attributes (input variables) to VAO
        auto& vertex_shader = shader_program.vertex_shader();
        for (auto& attr : vertex_shader.attributes()) {
            auto location = shader_program.query_attribute_location(attr.name);
            dbgfln("Binding shader attribute '%s' to location %d with offset %d",
                   attr.name.data(),
                   location,
                   attr.relative_offset);
            glEnableVertexArrayAttrib(vao_, location);
            glVertexArrayAttribFormat(vao_, location, attr.size, attr.type, attr.normalized, attr.relative_offset);
            glVertexArrayAttribBinding(vao_, location, vertex_array_binding_point);
        }

        dbgln("RenderableText object created");
    }

    ~RenderableText() { free_gpu_resources(); }

    void render() {
        /*
        xassert(vertex_count_ > 0, "You're trying to render non-existing data");
        glUseProgram(shader_program_id_); // bind shader
        glBindVertexArray(vao_);          // bind VAO
        glDrawArrays(GL_TRIANGLES, 0, vertex_count_);
        glBindVertexArray(0); // unbind VAO
        glUseProgram(0);      // unbind shader
         */
    }

    void set_text(const std::string& text, float x, float y, float scale, glm::vec3 color) {
        glUseProgram(shader_program_id_); // bind shader
        glUniform3f(glGetUniformLocation(shader_program_id_, "texture_color"), color.x, color.y, color.z);

        glBindVertexArray(vao_); // bind VAO

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
            glNamedBufferSubData(vbo_, 0, g_buffer_size, vertices.data());
            glDrawArrays(GL_TRIANGLES, 0, vertices.size());

            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th
            // pixels by 64 to get amount of pixels))
            current_x += (character_bitmap.advance_offset_x() >> 6) * scale;
        }

        glBindTextureUnit(0, 0); // unbind texture
        glBindVertexArray(0);    // unbind VAO
        glUseProgram(0);         // unbind shader
    }

    void free_gpu_resources() noexcept {
        if (vao_ > 0) {
            glDeleteVertexArrays(1, &vao_);
            vao_ = 0;
        }
        if (vbo_ > 0) {
            glDeleteBuffers(1, &vbo_);
            vbo_ = 0;
        }
    }

private:
    constexpr static auto g_buffer_size = sizeof(TextureCoordinates) * 6;
    const FontBitmapCache& font_bitmap_cache_;
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
    GLuint shader_program_id_ = 0;
};

} // namespace engine

#endif // ENGINE_RENDERABLETEXT_H

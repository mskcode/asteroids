#ifndef ENGINE_FONTBITMAPMAP_H
#define ENGINE_FONTBITMAPMAP_H

#include "Font.h"
#include "freetype.h"
#include "opengl.h"
#include <cstdint>
#include <glm/vec2.hpp>
#include <unordered_map>

namespace engine {

class FontCharacterBitmap final {
public:
    FontCharacterBitmap(uint8_t character,
                        GLuint texture_id,
                        FT_Pos advance_offset_x,
                        glm::ivec2 size,
                        glm::ivec2 bearing);
    FontCharacterBitmap(const FontCharacterBitmap&) = delete;
    FontCharacterBitmap(FontCharacterBitmap&& other) noexcept;
    ~FontCharacterBitmap();

    auto operator=(const FontCharacterBitmap&) -> FontCharacterBitmap& = delete;
    auto operator=(FontCharacterBitmap&& rhs) noexcept -> FontCharacterBitmap&;

    [[nodiscard]] auto character() const -> uint8_t;
    [[nodiscard]] auto texture_id() const -> GLuint;
    [[nodiscard]] auto advance_offset_x() const -> FT_Pos;
    [[nodiscard]] auto size() const -> const glm::ivec2&;
    [[nodiscard]] auto bearing() const -> const glm::ivec2&;

    void free_gpu_resources();

private:
    uint8_t character_ = 0;
    GLuint texture_id_ = 0;
    FT_Pos advance_offset_x_ = 0;
    glm::ivec2 size_{0, 0};
    glm::ivec2 bearing_{0, 0};
};

class FontBitmapMap final {
public:
    FontBitmapMap(const FontBitmapMap&) = delete;
    FontBitmapMap(FontBitmapMap&&) = delete;
    ~FontBitmapMap() = default;

    auto operator=(const FontBitmapMap&) -> FontBitmapMap& = delete;
    auto operator=(FontBitmapMap&&) -> FontBitmapMap& = delete;

    static auto from(const Font& font) -> std::unique_ptr<FontBitmapMap>;

private:
    std::unordered_map<uint8_t, FontCharacterBitmap> character_map_;

    FontBitmapMap(std::unordered_map<uint8_t, FontCharacterBitmap>&& character_map);
};

} // namespace engine

#endif // ENGINE_FONTBITMAPMAP_H

#pragma once

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

class FontBitmapCache final {
public:
    FontBitmapCache(const FontBitmapCache&) = delete;
    FontBitmapCache(FontBitmapCache&&) = delete;
    ~FontBitmapCache() = default;

    auto operator=(const FontBitmapCache&) -> FontBitmapCache& = delete;
    auto operator=(FontBitmapCache&&) -> FontBitmapCache& = delete;
    auto operator[](char c) const -> const FontCharacterBitmap&;

    static auto from(Font& font, FT_UInt font_size_height, FT_UInt font_size_width = 0)
        -> std::unique_ptr<FontBitmapCache>;

private:
    std::unordered_map<uint8_t, FontCharacterBitmap> character_map_;

    FontBitmapCache(std::unordered_map<uint8_t, FontCharacterBitmap>&& character_map);
};

} // namespace engine

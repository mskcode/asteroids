#pragma once

#include "Font.h"
#include "OpenGlObject.h"
#include "freetype.h"
#include "opengl.h"
#include <cstdint>
#include <glm/vec2.hpp>
#include <unordered_map>

namespace engine {

class FontBitmapCache;

class FontCharacterBitmap final {
    friend class FontBitmapCache;

public:
    FontCharacterBitmap() = default;
    FontCharacterBitmap(const FontCharacterBitmap&) = default;
    FontCharacterBitmap(FontCharacterBitmap&&) noexcept = default;
    ~FontCharacterBitmap() = default;

    auto operator=(const FontCharacterBitmap&) -> FontCharacterBitmap& = default;
    auto operator=(FontCharacterBitmap&&) noexcept -> FontCharacterBitmap& = default;

    [[nodiscard]] auto object() const -> OpenGlObject { return obj_; }
    [[nodiscard]] auto character() const -> uint8_t { return character_; }
    [[nodiscard]] auto advance_offset_x() const -> FT_Pos { return advance_offset_x_; }
    [[nodiscard]] auto size() const -> const glm::ivec2& { return size_; }
    [[nodiscard]] auto bearing() const -> const glm::ivec2& { return bearing_; }

private:
    FontCharacterBitmap(OpenGlObject obj,
                        uint8_t character,
                        FT_Pos advance_offset_x,
                        glm::ivec2 size,
                        glm::ivec2 bearing);

    OpenGlObject obj_;
    uint8_t character_{0};
    FT_Pos advance_offset_x_{0};
    glm::ivec2 size_{0, 0};
    glm::ivec2 bearing_{0, 0};
};

class FontBitmapCache final {
public:
    FontBitmapCache() = default;
    FontBitmapCache(const FontBitmapCache&) = default;
    FontBitmapCache(FontBitmapCache&&) = default;
    ~FontBitmapCache() = default;

    auto operator=(const FontBitmapCache&) -> FontBitmapCache& = default;
    auto operator=(FontBitmapCache&&) -> FontBitmapCache& = default;

    auto operator[](char c) const -> const FontCharacterBitmap&;

    static auto from(Font font, FontSize size) -> FontBitmapCache;

private:
    FontBitmapCache(std::unordered_map<uint8_t, FontCharacterBitmap>&& character_map);

    std::unordered_map<uint8_t, FontCharacterBitmap> character_map_;
};

class FontBitmapCacheRegistry final {
public:
    FontBitmapCacheRegistry() = default;
    FontBitmapCacheRegistry(const FontBitmapCacheRegistry&) = delete;
    FontBitmapCacheRegistry(FontBitmapCacheRegistry&&) = delete;
    ~FontBitmapCacheRegistry() noexcept = default;

    auto operator=(const FontBitmapCacheRegistry&) -> FontBitmapCacheRegistry& = delete;
    auto operator=(FontBitmapCacheRegistry&&) -> FontBitmapCacheRegistry& = delete;

    static auto instance() -> FontBitmapCacheRegistry&;

    auto create(u32 ext_id, Font font, FontSize size) -> FontBitmapCache&;
    auto find(u32 ext_id) -> FontBitmapCache&;

private:
    std::unordered_map<u32, FontBitmapCache> registry_map_;
};

} // namespace engine

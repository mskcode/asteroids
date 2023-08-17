#include "FontBitmapCache.h"
#include "../common/assertions.h"
#include "../common/debug.h"
#include <utility>

using namespace engine;

FontCharacterBitmap::FontCharacterBitmap(OpenGlObject obj,
                                         uint8_t character,
                                         FT_Pos advance_offset_x,
                                         glm::ivec2 size,
                                         glm::ivec2 bearing) :
    obj_(obj),
    character_(character),
    advance_offset_x_(advance_offset_x),
    size_(size),
    bearing_(bearing) {}

FontBitmapCache::FontBitmapCache(std::unordered_map<uint8_t, FontCharacterBitmap>&& character_map) :
    character_map_(std::move(character_map)) {}

auto FontBitmapCache::operator[](char c) const -> const FontCharacterBitmap& {
    return character_map_.at(static_cast<uint8_t>(c));
}

auto FontBitmapCache::from(Font font, FontSize size) -> FontBitmapCache {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    // FIXME we should probably restore the font size after we're done
    font.set_pixel_sizes(size);

    auto* face = font.face();
    std::unordered_map<uint8_t, FontCharacterBitmap> character_map;
    for (uint8_t ascii_code = 0; ascii_code < 128; ++ascii_code) {
        auto status = FT_Load_Char(face, ascii_code, FT_LOAD_RENDER);
        if (status != 0) {
            dbgfln("Failed to load font glyph for character %d", ascii_code);
            continue;
        }

        auto texture = OpenGlObjectManager::instance().allocate(OpenGlObjectType::TEXTURE);
        auto texture_id = texture.ogl_id();
        glBindTexture(GL_TEXTURE_2D, texture_id);

        glTextureParameteri(texture_id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(texture_id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTextureParameteri(texture_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(texture_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // define the texture storage requirements
        glTextureStorage2D(texture_id,
                           1,                         // number of texture levels; at least 1
                           GL_R8,                     // internal format; we're using red unsigned bytes
                           face->glyph->bitmap.width, // width of texture
                           face->glyph->bitmap.rows); // height of texture

        glTextureSubImage2D(texture_id,
                            0,                           // level of detail; Nth mipmap, 0 is base level
                            0,                           // x-offset
                            0,                           // y-offset
                            face->glyph->bitmap.width,   // width of texture
                            face->glyph->bitmap.rows,    // height of texture
                            GL_RED,                      // format of pixel data
                            GL_UNSIGNED_BYTE,            // pixel data type
                            face->glyph->bitmap.buffer); // bitmap data

        character_map.insert({ascii_code,
                              {texture,
                               ascii_code,
                               face->glyph->advance.x,
                               {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                               {face->glyph->bitmap_left, face->glyph->bitmap_top}}});
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // restore the original byte-alignment value

    return {std::move(character_map)};
}
auto FontBitmapCacheRegistry::instance() -> FontBitmapCacheRegistry& {
    static FontBitmapCacheRegistry the_instance;
    return the_instance;
}
auto FontBitmapCacheRegistry::create(u32 ext_id, Font font, FontSize size) -> FontBitmapCache& {
    XASSERTF(!registry_map_.contains(ext_id), "Font bitmap cache ID %u already exists", ext_id);
    auto cache = FontBitmapCache::from(font, size);
    registry_map_.insert({ext_id, std::move(cache)});
    return registry_map_.find(ext_id)->second;
}

auto FontBitmapCacheRegistry::find(u32 ext_id) -> FontBitmapCache& {
    auto it = registry_map_.find(ext_id);
    XASSERTF(it != registry_map_.end(), "Font bitmap cache ID %u doesn't exist", ext_id);
    return it->second;
}

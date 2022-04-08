#include "FontBitmapMap.h"
#include "../common/debug.h"

using namespace engine;

FontCharacterBitmap::FontCharacterBitmap(uint8_t character,
                                         GLuint texture_id,
                                         FT_Pos advance_offset_x,
                                         glm::ivec2 size,
                                         glm::ivec2 bearing) :
    character_(character),
    texture_id_(texture_id),
    advance_offset_x_(advance_offset_x),
    size_(size),
    bearing_(bearing) {}

FontCharacterBitmap::FontCharacterBitmap(FontCharacterBitmap&& other) noexcept :
    character_(other.character_),
    texture_id_(std::exchange(other.texture_id_, 0)),
    advance_offset_x_(other.advance_offset_x_),
    size_(other.size_),
    bearing_(other.bearing_) {}

auto FontCharacterBitmap::operator=(FontCharacterBitmap&& rhs) noexcept -> FontCharacterBitmap& {
    if (this != &rhs) {
        free_gpu_resources();
        character_ = rhs.character_;
        texture_id_ = std::exchange(rhs.texture_id_, 0);
        advance_offset_x_ = rhs.advance_offset_x_;
        size_ = rhs.size_;
        bearing_ = rhs.bearing_;
    }
    return *this;
}

FontCharacterBitmap::~FontCharacterBitmap() {
    free_gpu_resources();
}

auto FontCharacterBitmap::character() const -> uint8_t {
    return character_;
}

auto FontCharacterBitmap::texture_id() const -> GLuint {
    return texture_id_;
}

auto FontCharacterBitmap::advance_offset_x() const -> FT_Pos {
    return advance_offset_x_;
}

auto FontCharacterBitmap::size() const -> const glm::ivec2& {
    return size_;
}

auto FontCharacterBitmap::bearing() const -> const glm::ivec2& {
    return bearing_;
}

void FontCharacterBitmap::free_gpu_resources() {
    if (texture_id_ != 0) {
        dbgfln("Freeing font texture ID %d", texture_id_);
        glDeleteTextures(1, &texture_id_);
        texture_id_ = 0;
    }
}

FontBitmapMap::FontBitmapMap(std::unordered_map<uint8_t, FontCharacterBitmap>&& character_map) :
    character_map_(std::move(character_map)) {}

auto FontBitmapMap::from(const Font& font) -> std::unique_ptr<FontBitmapMap> {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    auto* face = font.face();
    std::unordered_map<uint8_t, FontCharacterBitmap> character_map;
    for (uint8_t ascii_code = 0; ascii_code < 128; ++ascii_code) {
        auto status = FT_Load_Char(face, ascii_code, FT_LOAD_RENDER);
        if (status != 0) {
            dbgfln("Failed to load font glyph for character %d", ascii_code);
            continue;
        }

        GLuint texture_id;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id); // bind texture
        glTexImage2D(GL_TEXTURE_2D,
                     0,                           // level of detail; Nth mipmap, 0 is base level
                     GL_RED,                      // internal format; but why this value?
                     face->glyph->bitmap.width,   // width of texture
                     face->glyph->bitmap.rows,    // height of texture
                     0,                           // border; must be 0
                     GL_RED,                      // format of pixel data
                     GL_UNSIGNED_BYTE,            // pixel data type
                     face->glyph->bitmap.buffer); // bitmap data

        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        FontCharacterBitmap fcb{ascii_code,
                                texture_id,
                                face->glyph->advance.x,
                                {face->glyph->bitmap.width, face->glyph->bitmap.rows},
                                {face->glyph->bitmap_left, face->glyph->bitmap_top}};

        character_map.insert({ascii_code, std::move(fcb)});

        glBindTexture(GL_TEXTURE_2D, 0); // unbind texture
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // restore the original value

    auto* ptr = new FontBitmapMap(std::move(character_map));
    return std::unique_ptr<FontBitmapMap>(ptr);
}

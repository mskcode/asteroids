#include "Font.h"
#include "../common/assertions.h"
#include "../common/debug.h"
#include <algorithm>
#include <vector>

using namespace engine;

Font::Font(u32 ext_id, FT_Face face) :
    ext_id_(ext_id),
    face_(face) {}

void Font::free() noexcept {
    if (!is_valid()) {
        return;
    }

    dbgfln("Freeing font face %u", ext_id_);
    auto status = FT_Done_Face(face_);
    if (status != 0) {
        std::fprintf(stderr, "Freeing FreeType font face failed");
    }

    face_ = nullptr;
    ext_id_ = 0;
}

void Font::set_pixel_sizes(FontSize size) {
    FT_Set_Pixel_Sizes(face_, size.width, size.height);
}

FontManager::FontManager() {
    dbgln("Initializing font manager");
    auto status = FT_Init_FreeType(&library_);
    VERIFY(status == 0);
}

FontManager::~FontManager() noexcept {
    destroy();
}

auto FontManager::instance() -> FontManager& {
    static FontManager the_instance;
    return the_instance;
}

auto FontManager::load(u32 ext_id, const std::string& path) -> Font {
    XASSERTF(!font_map_.contains(ext_id), "Font ID {} has already been loaded", ext_id);
    dbgfln("Loading font face from file %s as font ID %u", path.c_str(), ext_id);
    FT_Face face = nullptr;
    auto status = FT_New_Face(library_, path.data(), 0, &face);
    XASSERTF(status == 0, "Failed to load font from path {} (error: {})", path, status);

    Font font{ext_id, face};
    font_map_.insert({ext_id, font});
    return font;
}

auto FontManager::find(u32 ext_id) const -> Font {
    auto it = font_map_.find(ext_id);
    XASSERTF(it != font_map_.end(), "Font ID %u doesn't exist", ext_id);
    return it->second;
}

auto FontManager::free(Font font) noexcept -> void {
    XASSERTM(font.is_valid(), "Trying to free invalid font");

    // remove font from map
    auto it = font_map_.find(font.ext_id());
    XASSERTF(it != font_map_.end(), "Font ID %u doesn't exist", font.ext_id());
    font_map_.erase(it);

    // free font
    font.free();
}

auto FontManager::destroy() noexcept -> void {
    // NOTE since free(Font) modifies (deletes item) the object map we
    // cannot be iterating on the map at the same time. That's why we do this
    // copying thing here
    std::vector<Font> freeable_fonts;
    std::transform(font_map_.begin(), font_map_.end(), std::back_inserter(freeable_fonts), [](const auto& val) {
        return val.second;
    });

    for (auto& font : freeable_fonts) {
        free(font);
    }

    if (library_ != nullptr) {
        dbgln("Freeing font manager resource FreeType library");
        auto status = FT_Done_FreeType(library_);
        if (status != 0) {
            std::fprintf(stderr, "Freeing FreeType library failed");
        }
    }
}

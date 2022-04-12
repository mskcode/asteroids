#include "FontManager.h"
#include "../common/debug.h"
#include "FontBitmapCache.h"
#include <cstdio>

using namespace engine;

FontManager::FontManager() {
    dbgln("Initializing font manager");
    auto status = FT_Init_FreeType(&library_);
    if (status != 0) {}
}

FontManager::~FontManager() {
    free();
}

void FontManager::free() noexcept {
    for (auto& [key, value] : fonts_by_name_) {
        value->free();
    }

    if (library_ != nullptr) {
        dbgln("Freeing font manager resource FreeType library");
        auto status = FT_Done_FreeType(library_);
        if (status != 0) {
            std::fprintf(stderr, "Freeing FreeType library failed");
        }
    }
}

void FontManager::load_font(const std::string& name, const std::string& path) {
    if (fonts_by_name_.contains(name)) {
        throw std::runtime_error("Font name '" + name + "' has already been loaded");
    }
    fonts_by_name_.insert({name, Font::load(library_, path)});
}

auto FontManager::get_font(const std::string& name) const -> Font& {
    if (!fonts_by_name_.contains(name)) {
        throw std::runtime_error("Font name '" + name + "' does not exist");
    }
    return *fonts_by_name_.at(name).get();
}

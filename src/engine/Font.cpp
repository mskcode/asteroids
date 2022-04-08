#include "Font.h"
#include "../common/debug.h"

using namespace engine;

Font::Font(FT_Face face) :
    face_(face) {}

Font::~Font() {
    free();
}

void Font::free() noexcept {
    if (face_ != nullptr) {
        dbgln("Freeing font face");
        auto status = FT_Done_Face(face_);
        if (status != 0) {
            std::fprintf(stderr, "Freeing FreeType font face failed");
        }
        face_ = nullptr;
    }
}

auto Font::load(FT_Library library, const std::string& path) -> std::unique_ptr<Font> {
    dbgfln("Loading font face from file %s", path.c_str());
    FT_Face face = nullptr;
    auto status = FT_New_Face(library, path.data(), 0, &face);
    if (status != 0) {
        throw std::runtime_error("Failed to load font from path " + path);
    }
    return std::unique_ptr<Font>(new Font(face));
}

auto Font::face() const -> FT_Face {
    return face_;
}

void Font::set_pixel_sizes(FT_UInt pixel_height, FT_UInt pixel_width) {
    // leaving the pixel_width to 0 lets the face dynamically calculate the width based on the height
    FT_Set_Pixel_Sizes(face_, pixel_width, pixel_height);
}

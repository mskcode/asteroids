#ifndef ENGINE_FONT_H
#define ENGINE_FONT_H

#include "freetype.h"
#include <memory>
#include <string>

namespace engine {

class Font final {
public:
    ~Font();

    static auto load(FT_Library library, const std::string& path) -> std::unique_ptr<Font>;

    [[nodiscard]] auto face() const -> FT_Face;

    void free() noexcept;
    void set_pixel_sizes(FT_UInt pixel_width = 48, FT_UInt pixel_height = 0);

private:
    FT_Face face_ = nullptr; // pointer

    Font(FT_Face face);
};

} // namespace engine

#endif // ENGINE_FONT_H

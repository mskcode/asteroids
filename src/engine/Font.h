#pragma once

#include "freetype.h"
#include <memory>
#include <string>

namespace engine {

class Font final {
public:
    Font(const Font&) = delete;
    Font(Font&&) = delete;
    ~Font();

    auto operator=(const Font&) -> Font& = delete;
    auto operator=(Font&&) noexcept -> Font& = delete;

    static auto load(FT_Library library, const std::string& path) -> std::unique_ptr<Font>;

    [[nodiscard]] auto face() const -> FT_Face;

    void free() noexcept;
    void set_pixel_sizes(FT_UInt pixel_height, FT_UInt pixel_width = 0);

private:
    FT_Face face_ = nullptr; // pointer

    Font(FT_Face face);
};

} // namespace engine

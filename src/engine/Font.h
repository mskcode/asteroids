#pragma once

#include "../common/typealiases.h"
#include "Resource.h"
#include "freetype.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace engine {

struct FontSize {
    FT_UInt height{10};
    // leaving the pixel_width to 0 lets the face dynamically calculate the
    // width based on the height
    FT_UInt width{0};
};

class FontManager;

class Font final {
    friend class FontManager;

public:
    Font() = default;
    Font(const Font&) = default;
    Font(Font&&) noexcept = default;
    ~Font() noexcept = default;

    auto operator=(const Font&) -> Font& = default;
    auto operator=(Font&&) noexcept -> Font& = default;

    [[nodiscard]] auto ext_id() const -> u32 { return ext_id_; }
    [[nodiscard]] auto face() const -> FT_Face { return face_; }
    [[nodiscard]] auto is_valid() const -> bool { return face_ != nullptr; }

    auto set_pixel_sizes(FontSize size) -> void;

private:
    Font(u32 ext_id, FT_Face face);

    auto free() noexcept -> void;

    u32 ext_id_{0};
    FT_Face face_{nullptr};
    FontSize default_font_size_;
};

class FontManager final {
public:
    FontManager();
    FontManager(const FontManager&) = delete;
    FontManager(FontManager&&) noexcept = delete;
    ~FontManager() noexcept;

    auto operator=(const FontManager&) -> FontManager& = delete;
    auto operator=(FontManager&&) noexcept -> FontManager& = delete;

    static auto instance() -> FontManager&;

    auto load(Resource id, const std::string& path) -> Font;
    auto find(Resource id) const -> Font;
    auto free(Font font) noexcept -> void;
    auto destroy() noexcept -> void;

private:
    FT_Library library_{nullptr};
    std::unordered_map<u32, Font> font_map_;
};

} // namespace engine

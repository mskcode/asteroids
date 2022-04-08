#ifndef ENGINE_FONTMANAGER_H
#define ENGINE_FONTMANAGER_H

#include "Font.h"
#include "FontBitmapMap.h"
#include "freetype.h"
#include <memory>
#include <string>
#include <unordered_map>

namespace engine {

class FontManager final {
public:
    FontManager();
    ~FontManager();

    void free() noexcept;
    void load_font(const std::string& name, const std::string& path);
    auto get_font(const std::string& name) const -> const Font&;

private:
    FT_Library library_ = nullptr; // pointer
    std::unordered_map<std::string, std::unique_ptr<Font>> fonts_by_name_;
};

} // namespace engine

#endif // ENGINE_FONTMANAGER_H

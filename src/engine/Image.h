#pragma once

#include "opengl.h"
#include <stb/stb_image.h>
#include <string>

namespace engine {

class Image {
public:
    Image(const Image&) = delete;
    Image(Image&& other) noexcept;
    ~Image();

    auto operator=(const Image&) -> Image& = delete;
    auto operator=(Image&& rhs) noexcept -> Image&;

    static auto load(const std::string& file_path) -> Image;

    [[nodiscard]] auto width() const -> GLsizei { return width_; }
    [[nodiscard]] auto height() const -> GLsizei { return height_; }
    [[nodiscard]] auto color_channels() const -> GLsizei { return color_channels_; }
    [[nodiscard]] auto data() -> unsigned char* { return data_; }

    auto free() -> void;

private:
    Image(std::string file_path, int width, int height, int color_channels, stbi_uc* data);

    std::string file_path_;
    GLsizei width_{0};
    GLsizei height_{0};
    GLsizei color_channels_{0};
    unsigned char* data_{nullptr};
};

} // namespace engine

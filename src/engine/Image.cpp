#include "Image.h"
#include "../common/assertions.h"
#include "../common/debug.h"
#include <utility>

using namespace engine;

Image::Image(std::string file_path, int width, int height, int color_channels, stbi_uc* data) :
    file_path_(std::move(file_path)),
    width_(width),
    height_(height),
    color_channels_(color_channels),
    data_(data) {}

Image::Image(Image&& other) noexcept :
    file_path_(std::exchange(other.file_path_, "")),
    width_(std::exchange(other.width_, 0)),
    height_(std::exchange(other.height_, 0)),
    color_channels_(std::exchange(other.color_channels_, 0)),
    data_(std::exchange(other.data_, nullptr)) {}

Image::~Image() {
    free();
}

auto Image::operator=(Image&& rhs) noexcept -> Image& {
    if (this != &rhs) {
        free();
        file_path_ = std::exchange(rhs.file_path_, "");
        width_ = std::exchange(rhs.width_, 0);
        height_ = std::exchange(rhs.height_, 0);
        color_channels_ = std::exchange(rhs.color_channels_, 0);
        data_ = std::exchange(rhs.data_, nullptr);
    }
    return *this;
}

auto Image::load(const std::string& file_path) -> Image {
    dbgfln("Loading image %s", file_path.c_str());
    int width;
    int height;
    int color_channels;
    stbi_uc* data = stbi_load(file_path.c_str(), &width, &height, &color_channels, /* desired_channels= */ 0);
    // FIXME we could call stbi_failure_reason() to get the reason why this failed
    XASSERTF(data != nullptr, "Failed to load image from path {}", file_path);
    return {file_path,
            static_cast<GLsizei>(width),
            static_cast<GLsizei>(height),
            static_cast<GLsizei>(color_channels),
            static_cast<unsigned char*>(data)};
}
auto Image::free() -> void {
    if (data_ != nullptr) {
        dbgfln("Freeing image %s", file_path_.c_str());
        stbi_image_free(data_);
        data_ = nullptr;
    }
}

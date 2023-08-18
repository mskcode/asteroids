#pragma once

#include "../common/typealiases.h"
#include "OpenGlObject.h"
#include "Resource.h"
#include "opengl.h"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace engine {

class TextureRegistry;

class Texture {
    friend class TextureRegistry;

public:
    Texture() = default;
    Texture(const Texture&) = default;
    Texture(Texture&& other) noexcept = default;
    ~Texture() = default;

    auto operator=(const Texture&) -> Texture& = default;
    auto operator=(Texture&&) noexcept -> Texture& = default;

    [[nodiscard]] auto object() const -> const OpenGlObject { return obj_; }

    auto bind() const -> void;
    auto unbind() const -> void;

private:
    Texture(OpenGlObject obj);

    OpenGlObject obj_;
};

class TextureRegistry {
public:
    TextureRegistry() = default;
    TextureRegistry(const TextureRegistry&) = delete;
    TextureRegistry(TextureRegistry&&) noexcept = delete;
    ~TextureRegistry() = default;

    auto operator=(const TextureRegistry&) -> TextureRegistry& = delete;
    auto operator=(TextureRegistry&&) noexcept -> TextureRegistry& = delete;

    static auto instance() -> TextureRegistry&;

    auto load_texture(Resource id, const std::string& image_file_path) -> Texture;
    auto find(Resource id) const -> Texture;

private:
    std::unordered_map<u32, Texture> texture_map_;
};

} // namespace engine

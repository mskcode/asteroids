#pragma once

#include "../common/typealiases.h"
#include "opengl.h"
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace engine {

class Texture;
class TextureRegistry;

class TextureId final {
    friend class TextureRegistry;
    friend class Texture;

public:
    TextureId() = default;
    TextureId(const TextureId&) = default;
    TextureId(TextureId&&) noexcept = default;

    auto operator=(const TextureId&) -> TextureId& = default;
    auto operator=(TextureId&&) noexcept -> TextureId& = default;

    [[nodiscard]] auto external_id() const -> unsigned int { return external_id_; }
    [[nodiscard]] auto ogl_id() const -> GLuint { return ogl_id_; }
    [[nodiscard]] auto is_valid() const -> bool { return ogl_id_ > 0; }

private:
    TextureId(u32 external_id, GLuint ogl_id);

    u32 external_id_{0}; // user given ID
    GLuint ogl_id_{0};   // OpenGL generated ID
};

class Texture {
    friend class TextureRegistry;

public:
    Texture() = default;
    Texture(const Texture&) = default;
    Texture(Texture&& other) noexcept = default;
    ~Texture() = default;

    auto operator=(const Texture&) -> Texture& = default;
    auto operator=(Texture&& rhs) noexcept -> Texture& = default;

    [[nodiscard]] auto id() const -> const TextureId& { return texture_id_; }

    auto free_gpu_resources() -> void;
    auto bind() const -> void;
    auto unbind() const -> void;

private:
    Texture(TextureId texture_id);

    TextureId texture_id_;
};

class TextureRegistry {
public:
    TextureRegistry() = default;
    TextureRegistry(const TextureRegistry&) = delete;
    TextureRegistry(TextureRegistry&&) noexcept = delete;
    ~TextureRegistry();

    auto operator=(const TextureRegistry&) -> TextureRegistry& = delete;
    auto operator=(TextureRegistry&&) noexcept -> TextureRegistry& = delete;

    auto load_texture(u32 external_id, const std::string& image_file_path) -> Texture;
    auto find(u32 external_id) const -> std::optional<Texture>;

private:
    auto free_all_textures() -> void;

    std::unordered_map<u32, Texture> texture_map_;
};

} // namespace engine

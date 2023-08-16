#pragma once

#include "../common/typealiases.h"
#include "opengl.h"
#include <cstdarg>
#include <unordered_map>

namespace engine {

enum class OpenGlObjectType {
    UNKNOWN = 0,
    VAO,
    VBO,
    EBO,
    SHADER,
    SHADER_PROGRAM,
    TEXTURE,
};

class OpenGlObject final {
    friend class OpenGlObjectManager;

public:
    OpenGlObject() = default;
    OpenGlObject(const OpenGlObject&) = default;
    OpenGlObject(OpenGlObject&&) noexcept = default;
    ~OpenGlObject() = default;

    auto operator=(const OpenGlObject&) -> OpenGlObject& = default;
    auto operator=(OpenGlObject&&) noexcept -> OpenGlObject& = default;

    [[nodiscard]] auto type() const -> OpenGlObjectType { return type_; }
    [[nodiscard]] auto ext_id() const -> u32 { return ext_id_; }
    [[nodiscard]] auto ogl_id() const -> GLuint { return ogl_id_; }
    [[nodiscard]] auto is_valid() const -> bool { return ogl_id_ > 0; }

private:
    OpenGlObject(OpenGlObjectType type, u32 ext_id, GLuint ogl_id);

    auto free() noexcept -> void;
    auto invalidate() noexcept -> void { ogl_id_ = 0; }

    OpenGlObjectType type_{0};
    u32 ext_id_{0};
    GLuint ogl_id_{0};
};

// FIXME these might need renaming
using ext_id_object_map = std::unordered_map<u32, OpenGlObject>;
using object_type_map = std::unordered_map<OpenGlObjectType, ext_id_object_map>;

class OpenGlObjectManager final {
public:
    OpenGlObjectManager() = default;
    OpenGlObjectManager(const OpenGlObjectManager&) = delete;
    OpenGlObjectManager(OpenGlObjectManager&&) noexcept = delete;
    ~OpenGlObjectManager() noexcept;

    auto operator=(const OpenGlObjectManager&) = delete;
    auto operator=(OpenGlObjectManager&&) noexcept = delete;

    static auto instance() -> OpenGlObjectManager&;

    auto allocate(u32 ext_id, OpenGlObjectType type, ...) -> OpenGlObject;
    auto allocate(OpenGlObjectType type, ...) -> OpenGlObject;
    auto contains(OpenGlObjectType type, u32 ext_id) const -> bool;
    auto find(OpenGlObjectType type, u32 ext_id) const -> OpenGlObject;
    auto free(OpenGlObject obj) noexcept -> void;
    auto free_all() noexcept -> void;

private:
    auto allocate_impl(u32 ext_id, OpenGlObjectType type, std::va_list args) -> OpenGlObject;

    object_type_map object_map_;
};

} // namespace engine

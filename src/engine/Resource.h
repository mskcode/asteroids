#pragma once

#include "../common/typealiases.h"

namespace engine {

enum class ResourceType {
    UNKNOWN = 0,
    SHADER_PROGRAM,
    TEXTURE,
    FONT,
    FONT_BITMAP_CACHE,
};

class Resource final {
public:
    Resource(ResourceType type, u32 id) :
        type_(type),
        id_(id) {}

    operator u32() const { return id_; }
    operator int() const { return static_cast<int>(id_); }

    [[nodiscard]] auto type() const -> ResourceType { return type_; }
    [[nodiscard]] auto id() const -> u32 { return id_; }

private:
    ResourceType type_;
    u32 id_;
};

} // namespace engine

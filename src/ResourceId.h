#pragma once

#include "engine/Resource.h"

namespace game {

// NOLINTBEGIN(readability-identifier-naming)

struct ShaderProgramResources final {
    inline static const engine::Resource DEFAULT{engine::ResourceType::SHADER_PROGRAM, 1};
    inline static const engine::Resource GLYPH{engine::ResourceType::SHADER_PROGRAM, 2};
};

struct TextureResources final {
    inline static const engine::Resource SMILEY{engine::ResourceType::TEXTURE, 1};
};

struct FontResources final {
    inline static const engine::Resource ARCADE{engine::ResourceType::FONT, 1};
};

struct FontBitmapCacheResources final {
    inline static const engine::Resource ARCADE_48{engine::ResourceType::FONT_BITMAP_CACHE, 1};
};

// NOLINTEND(readability-identifier-naming)

} // namespace game

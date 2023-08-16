#include "Texture.h"
#include "../common/assertions.h"
#include "../common/debug.h"
#include "Image.h"
#include "openglerror.h"
#include <utility>

using namespace engine;

TextureId::TextureId(unsigned int external_id, GLuint ogl_id) :
    external_id_(external_id),
    ogl_id_(ogl_id) {}

Texture::Texture(TextureId texture_id) :
    texture_id_(texture_id) {}

auto Texture::free_gpu_resources() -> void {
    if (texture_id_.is_valid()) {
        auto id = texture_id_.ogl_id();
        dbgfln("Freeing texture ID %d", id);
        glDeleteTextures(1, &id);
        texture_id_ = TextureId();
    }
}
auto Texture::bind() const -> void {
    XASSERTM(texture_id_.is_valid(), "Trying to bind invalid texture");
    glBindTexture(GL_TEXTURE_2D, texture_id_.ogl_id());
}

auto Texture::unbind() const -> void {
    XASSERTM(texture_id_.is_valid(), "Trying to unbind invalid texture");
    glBindTexture(GL_TEXTURE_2D, 0);
}

TextureRegistry::~TextureRegistry() {
    free_all_textures();
}

auto TextureRegistry::load_texture(u32 external_id, const std::string& image_file_path) -> Texture {
    auto image = Image::load(image_file_path);

    // TODO more error checking

    // allocate texture
    GLuint opengl_texture_id;
    GL_CHECK(glGenTextures(1, &opengl_texture_id));

    dbgfln("Creating texture ID %d", opengl_texture_id);

    // bind texture so we can do something with it
    glBindTexture(GL_TEXTURE_2D, opengl_texture_id);

    // set texture wrapping / filtering options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // create texture from image data
    glTexImage2D(GL_TEXTURE_2D,
                 /* level= */ 0,
                 GL_RGB,
                 image.width(),
                 image.height(),
                 /* border= */ 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 image.data());

    // create required mipmaps for the texture
    glGenerateMipmap(GL_TEXTURE_2D);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // add texture to map and return reference to it
    texture_map_.emplace(external_id, Texture({external_id, opengl_texture_id}));
    return texture_map_.find(external_id)->second;
}

auto TextureRegistry::find(u32 external_id) const -> std::optional<Texture> {
    auto it = texture_map_.find(external_id);
    if (it == texture_map_.end()) {
        return {};
    }
    return it->second;
}

auto TextureRegistry::free_all_textures() -> void {
    for (auto& [key, value] : texture_map_) {
        value.free_gpu_resources();
    }
}

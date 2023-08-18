#include "Texture.h"
#include "../common/assertions.h"
#include "../common/debug.h"
#include "Image.h"

using namespace engine;

Texture::Texture(OpenGlObject obj) :
    obj_(obj) {}

auto Texture::bind() const -> void {
    XASSERTM(obj_.is_valid(), "Trying to bind invalid texture");
    glBindTexture(GL_TEXTURE_2D, obj_.ogl_id());
}

auto Texture::unbind() const -> void {
    XASSERTM(obj_.is_valid(), "Trying to unbind invalid texture");
    glBindTexture(GL_TEXTURE_2D, 0);
}

auto TextureRegistry::instance() -> TextureRegistry& {
    static TextureRegistry the_instance;
    return the_instance;
}

auto TextureRegistry::load_texture(Resource id, const std::string& image_file_path) -> Texture {
    XASSERT(id.type() == ResourceType::TEXTURE);
    auto image = Image::load(image_file_path);

    dbgfln("Creating texture ID %u", id.id());

    // allocate texture
    auto ogl_texture_obj = OpenGlObjectManager::instance().allocate(OpenGlObjectType::TEXTURE);
    Texture texture{ogl_texture_obj};

    // bind texture so we can do something with it
    texture.bind();

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
    texture.unbind();

    // add texture to map and return reference to it
    texture_map_.insert({id, texture});
    return texture_map_.find(id)->second;
}

auto TextureRegistry::find(Resource id) const -> Texture {
    XASSERT(id.type() == ResourceType::TEXTURE);
    auto it = texture_map_.find(id);
    XASSERT(it != texture_map_.end());
    return it->second;
}

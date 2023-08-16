#include "OpenGlObject.h"
#include "../common/assertions.h"
#include "../common/debug.h"
#include "openglerror.h"
#include <algorithm>
#include <array>
#include <climits>
#include <iterator>
#include <vector>

using namespace engine;

OpenGlObject::OpenGlObject(OpenGlObjectType type, u32 ext_id, GLuint ogl_id) :
    type_(type),
    ext_id_(ext_id),
    ogl_id_(ogl_id) {
    XASSERTM(type != OpenGlObjectType::UNKNOWN, "type cannot be UNKNOWN");
    XASSERTM(ext_id > 0, "ext_id must be greater than zero");
}

auto OpenGlObject::free() noexcept -> void {
    if (!is_valid()) {
        return;
    }

    dbgfln("Freeing OpenGlObject type=%d, ext_id=%u, ogl_id=%u", (int)type_, ext_id_, ogl_id_);

    switch (type_) {
    case OpenGlObjectType::VAO:
        glDeleteVertexArrays(1, &ogl_id_);
        break;

    case OpenGlObjectType::VBO:
    case OpenGlObjectType::EBO:
        glDeleteBuffers(1, &ogl_id_);
        break;

    case OpenGlObjectType::SHADER:
        glDeleteShader(ogl_id_);
        break;

    case OpenGlObjectType::SHADER_PROGRAM:
        glDeleteProgram(ogl_id_);
        break;

    case OpenGlObjectType::TEXTURE:
        glDeleteTextures(1, &ogl_id_);
        break;

    default:
        VERIFY_NOT_REACHED();
    }

    // let's invalidate the object since we have the guard on top
    invalidate();
}

OpenGlObjectManager::~OpenGlObjectManager() noexcept {
    free_all();
}

auto OpenGlObjectManager::instance() -> OpenGlObjectManager& {
    static OpenGlObjectManager the_instance;
    return the_instance;
}

auto OpenGlObjectManager::allocate_impl(u32 ext_id, OpenGlObjectType type, std::va_list args) -> OpenGlObject {
    XASSERTF(!contains(type, ext_id), "OpenGlObject ID {} (type {}) already exists", ext_id, (int)type);

    dbgfln("Allocating OpenGlObject type=%d, ext_id=%u", (int)type, ext_id);

    GLuint id;
    switch (type) {
    case OpenGlObjectType::VAO:
        GL_CHECK(glCreateVertexArrays(1, &id));
        break;
    case OpenGlObjectType::VBO:
    case OpenGlObjectType::EBO:
        GL_CHECK(glCreateBuffers(1, &id));
        break;
    case OpenGlObjectType::SHADER: {
        GLenum shader_type = va_arg(args, GLenum);
        dbgfln("shader_type=%x", shader_type);
        XASSERT(shader_type == GL_COMPUTE_SHADER || shader_type == GL_VERTEX_SHADER ||
                shader_type == GL_TESS_CONTROL_SHADER || shader_type == GL_TESS_EVALUATION_SHADER ||
                shader_type == GL_GEOMETRY_SHADER || shader_type == GL_FRAGMENT_SHADER);
        id = glCreateShader(shader_type);
    } break;
    case OpenGlObjectType::SHADER_PROGRAM:
        id = glCreateProgram();
        break;
    case OpenGlObjectType::TEXTURE:
        GL_CHECK(glGenTextures(1, &id));
        break;
    default:
        VERIFY_NOT_REACHED();
    }

    VERIFY(id > 0);

    OpenGlObject obj{type, ext_id, id};
    object_map_[type].insert({ext_id, obj});
    return obj;
}

auto OpenGlObjectManager::allocate(u32 ext_id, OpenGlObjectType type, ...) -> OpenGlObject {
    std::va_list args;
    va_start(args, type);
    auto obj = allocate_impl(ext_id, type, args);
    va_end(args);
    return obj;
}

auto OpenGlObjectManager::allocate(OpenGlObjectType type, ...) -> OpenGlObject {
    u32 generated_ext_id{0};
    auto& objects_per_type_map = object_map_[type];
    for (u32 i = UINT32_MAX; i > 0; --i) {
        if (!objects_per_type_map.contains(i)) {
            generated_ext_id = i;
            break;
        }
    }

    va_list args;
    va_start(args, type);
    auto obj = allocate_impl(generated_ext_id, type, args);
    va_end(args);
    return obj;
}

auto OpenGlObjectManager::contains(OpenGlObjectType type, u32 ext_id) const -> bool {
    auto objects_per_type_map = object_map_.find(type);
    if (objects_per_type_map != object_map_.end()) {
        return objects_per_type_map->second.contains(ext_id);
    }
    return false;
}

auto OpenGlObjectManager::find(OpenGlObjectType type, u32 ext_id) const -> OpenGlObject {
    auto objects_per_type_map = object_map_.find(type);
    XASSERTF(objects_per_type_map != object_map_.end(), "object map for type {} doesn't exist", (int)type);

    auto it = objects_per_type_map->second.find(ext_id);
    XASSERTF(it != objects_per_type_map->second.end(), "object {}/{} doesn't exist", (int)type, ext_id);

    return it->second;
}

auto OpenGlObjectManager::free(OpenGlObject obj) noexcept -> void {
    XASSERTM(obj.is_valid(), "trying to free invalid object");

    // find map for given object types
    auto maybe_map = object_map_.find(obj.type());
    XASSERTM(maybe_map != object_map_.end(), "type map for objects doesn't exist");
    auto& map = maybe_map->second;

    // remove object from map
    auto it = map.find(obj.ext_id());
    if (it != map.end()) {
        map.erase(it);
    }

    // free object
    obj.free();
}

auto OpenGlObjectManager::free_all() noexcept -> void {
    // NOTE since free(OpenGlObject) modifies (deletes item) the object map we
    // cannot be iterating on the map at the same time. That's why we do this
    // copying thing here
    for (auto& [type, map] : object_map_) {
        std::vector<OpenGlObject> freeable_objects;
        std::transform(map.begin(), map.end(), std::back_inserter(freeable_objects), [](const auto& val) {
            return val.second;
        });

        for (auto& obj : freeable_objects) {
            free(obj);
        }
    }
}

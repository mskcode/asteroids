#include "Shader.h"
#include "OpenglException.h"
#include "debug.h"
#include "fileutils.h"

using namespace opengl;

Shader::Shader(GLenum type, const std::string_view& path, std::vector<VertexShaderAttribute> attributes)
    : type_(type),
      attributes_(std::move(attributes)) {
    dbgfln("Loading shader type %d from file: %s", type, path.data());
    auto source = fileutils::read_file(path);

    id_ = glCreateShader(type);
    dbgfln("Creating shader ID %d (shader_type=%d)", id_, type);
    const char* const p = source.c_str();
    glShaderSource(id_, 1, &p, nullptr);
    glCompileShader(id_);

    int success;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
    if (success != GL_TRUE) {
        constexpr size_t buffer_size{512};
        char log[buffer_size];
        glGetShaderInfoLog(id_, buffer_size, nullptr, log);
        throw_gl("Compiling shader " + std::string(path) + " failed: " + std::string(log));
    }
}

Shader::Shader(Shader&& other) noexcept
    : type_(other.type_),
      id_(std::exchange(other.id_, 0)),
      attributes_(std::move(other.attributes_)) {}

Shader::~Shader() {
    free_gpu_resources();
}

auto Shader::operator=(Shader&& rhs) noexcept -> Shader& {
    if (this != &rhs) {
        free_gpu_resources();
        id_ = std::exchange(rhs.id_, 0);
        type_ = rhs.type_;
        attributes_ = std::move(rhs.attributes_);
    }
    return *this;
}

auto Shader::id() const -> GLuint {
    return id_;
}

auto Shader::type() const -> GLenum {
    return type_;
}

auto Shader::attributes() const -> const std::vector<VertexShaderAttribute>& {
    return attributes_;
}

auto Shader::is_vertex_shader() const -> bool {
    return type_ == GL_VERTEX_SHADER;
}

auto Shader::is_fragment_shader() const -> bool {
    return type_ == GL_FRAGMENT_SHADER;
}

void Shader::free_gpu_resources() noexcept {
    if (id_ != 0) {
        dbgfln("Freeing shader ID %d", id_);
        glDeleteShader(id_);
        id_ = 0;
    }
}

#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include "glincludes.h"
#include "Renderable.h"

namespace asteroids {

class Spaceship final : public Renderable {
public:
    Spaceship();

    void render(GLFWwindow *window) override;

private:
    GLuint vertex_array_object_;
    GLuint vertex_buffer_object_;
    GLuint vertex_shader_;
    GLuint fragment_shader_;
    GLuint program_;
    GLint mvp_location_;
    GLint vpos_location_;
    GLint vcol_location_;

    void initialize_objects();

    void initialize_shaders();
};

} // namespace

#endif //ASTEROIDS_SPACESHIP_H

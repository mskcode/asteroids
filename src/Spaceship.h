#ifndef ASTEROIDS_SPACESHIP_H
#define ASTEROIDS_SPACESHIP_H

#include "opengl.h"
#include "Renderable.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Vertex.h"

namespace asteroids {

class Spaceship final : public Renderable {
public:
    Spaceship();

    ~Spaceship();

    void render(GLFWwindow *window) override;

private:
    opengl::ShaderProgram *shader_program_;
    opengl::Vertex *vertex_;

    void initialize_shaders();
};

} // namespace

#endif //ASTEROIDS_SPACESHIP_H

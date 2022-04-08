#include "KeyboardInputComponent.h"
#include "GameActor.h"

using namespace asteroids;

KeyboardInputComponent::KeyboardInputComponent(const opengl::Keyboard& keyboard) :
    keyboard_(keyboard) {}

void KeyboardInputComponent::update(GameActor& game_actor) {
    game_actor.velocity().reset();
    if (keyboard_[GLFW_KEY_UP].is_down()) {
        game_actor.velocity().y_velocity = 0.1f;
    }
    if (keyboard_[GLFW_KEY_DOWN].is_down()) {
        game_actor.velocity().y_velocity = -0.1f;
    }
    if (keyboard_[GLFW_KEY_LEFT].is_down()) {
        game_actor.velocity().x_velocity = -0.1f;
    }
    if (keyboard_[GLFW_KEY_RIGHT].is_down()) {
        game_actor.velocity().x_velocity = 0.1f;
    }
}

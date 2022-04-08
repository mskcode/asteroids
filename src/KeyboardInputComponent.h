#ifndef ASTEROIDS_KEYBOARDINPUTCOMPONENT_H
#define ASTEROIDS_KEYBOARDINPUTCOMPONENT_H

#include "InputComponent.h"
#include "opengl/Keyboard.h"
namespace asteroids {

class KeyboardInputComponent : public InputComponent {
public:
    KeyboardInputComponent(const opengl::Keyboard& keyboard);
    KeyboardInputComponent(const KeyboardInputComponent&) = delete;
    KeyboardInputComponent(KeyboardInputComponent&&) = delete;
    ~KeyboardInputComponent() override = default;

    void update(GameActor& game_actor) override;

private:
    const opengl::Keyboard& keyboard_;
};

} // namespace asteroids

#endif // ASTEROIDS_KEYBOARDINPUTCOMPONENT_H

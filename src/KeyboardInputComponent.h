#pragma once

#include "InputComponent.h"
#include "engine/Keyboard.h"

namespace game {

class KeyboardInputComponent : public InputComponent {
public:
    KeyboardInputComponent(const engine::Keyboard& keyboard);
    KeyboardInputComponent(const KeyboardInputComponent&) = delete;
    KeyboardInputComponent(KeyboardInputComponent&&) = delete;
    ~KeyboardInputComponent() override = default;

    void update(GameActor& game_actor) override;

private:
    const engine::Keyboard& keyboard_;
};

} // namespace game

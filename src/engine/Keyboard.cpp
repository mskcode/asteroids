#include "Keyboard.h"

using namespace engine;

auto Keyboard::operator[](int key) -> KeyState& {
    return key_states_[key];
}

auto Keyboard::operator[](int key) const -> const KeyState& {
    return key_states_[key];
}

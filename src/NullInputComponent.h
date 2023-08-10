#pragma once

#include "InputComponent.h"

namespace game {

class NullInputComponent : public InputComponent {
public:
    void update(GameActor& game_actor) override {}
};

} // namespace game

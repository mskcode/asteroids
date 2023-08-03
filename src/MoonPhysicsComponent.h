#pragma once

#include "PhysicsComponent.h"

namespace game {

class GameActor;

class MoonPhysicsComponent : public PhysicsComponent {
public:
    void update(GameActor& game_actor) override;
};

} // namespace game

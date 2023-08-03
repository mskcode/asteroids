#pragma once

#include "GameComponent.h"

namespace game {

class GameActor;

class PhysicsComponent : public GameComponent {
public:
    virtual void update(GameActor& game_actor) = 0;
};

} // namespace game

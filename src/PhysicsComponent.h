#ifndef GAME_PHYSICSCOMPONENT_H
#define GAME_PHYSICSCOMPONENT_H

#include "GameComponent.h"

namespace game {

class GameActor;

class PhysicsComponent : public GameComponent {
public:
    virtual void update(GameActor& game_actor) = 0;
};

} // namespace game

#endif // GAME_PHYSICSCOMPONENT_H

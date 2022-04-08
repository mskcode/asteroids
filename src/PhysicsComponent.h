#ifndef ASTEROIDS_PHYSICSCOMPONENT_H
#define ASTEROIDS_PHYSICSCOMPONENT_H

#include "GameComponent.h"

namespace asteroids {

class GameActor;

class PhysicsComponent : public GameComponent {
public:
    virtual void update(GameActor& game_actor) = 0;
};

} // namespace asteroids

#endif // ASTEROIDS_PHYSICSCOMPONENT_H

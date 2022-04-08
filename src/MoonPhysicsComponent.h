#ifndef ASTEROIDS_MOONPHYSICSCOMPONENT_H
#define ASTEROIDS_MOONPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"

namespace asteroids {

class GameActor;

class MoonPhysicsComponent : public PhysicsComponent {
public:
    void update(GameActor& game_actor) override;
};

} // namespace asteroids

#endif // ASTEROIDS_MOONPHYSICSCOMPONENT_H

#ifndef GAME_MOONPHYSICSCOMPONENT_H
#define GAME_MOONPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"

namespace game {

class GameActor;

class MoonPhysicsComponent : public PhysicsComponent {
public:
    void update(GameActor& game_actor) override;
};

} // namespace game

#endif // GAME_MOONPHYSICSCOMPONENT_H

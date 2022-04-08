#ifndef ASTEROIDS_INPUTCOMPONENT_H
#define ASTEROIDS_INPUTCOMPONENT_H

#include "GameComponent.h"

namespace asteroids {

class GameActor;

class InputComponent : public GameComponent {
public:
    virtual void update(GameActor& game_actor) = 0;
};

} // namespace asteroids

#endif // ASTEROIDS_INPUTCOMPONENT_H

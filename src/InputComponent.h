#ifndef GAME_INPUTCOMPONENT_H
#define GAME_INPUTCOMPONENT_H

#include "GameComponent.h"

namespace game {

class GameActor;

class InputComponent : public GameComponent {
public:
    virtual void update(GameActor& game_actor) = 0;
};

} // namespace game

#endif // GAME_INPUTCOMPONENT_H

#ifndef GAME_UPDATEABLE_H
#define GAME_UPDATEABLE_H

namespace game {

class Updateable {
public:
    virtual void update() = 0;
};

} // namespace game

#endif // GAME_UPDATEABLE_H

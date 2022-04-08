#ifndef GAME_RENDERABLE_H
#define GAME_RENDERABLE_H

namespace game {

class Renderable {
public:
    virtual void render() const = 0;
};

} // namespace game

#endif // GAME_RENDERABLE_H

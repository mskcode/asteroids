#pragma once

namespace game {

class Renderable {
public:
    virtual void render() const = 0;
};

} // namespace game

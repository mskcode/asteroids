#ifndef ASTEROIDS_GAMEACTOR_H
#define ASTEROIDS_GAMEACTOR_H

#include "GraphicsComponent.h"
#include "InputComponent.h"
#include "PhysicsComponent.h"
#include "Renderable.h"
#include "Updateable.h"
#include <memory>

namespace asteroids {

struct Coordinates2D final {
    float x = 0;
    float y = 0;
};

struct Coordinates3D final {
    float x;
    float y;
    float z;
};

struct Velocity2D final {
    float x_velocity = 0;
    float y_velocity = 0;

    void reset() {
        x_velocity = 0;
        y_velocity = 0;
    }
};

class GameActor final : public Renderable, public Updateable {
public:
    GameActor(std::unique_ptr<InputComponent> input,
              std::unique_ptr<PhysicsComponent> physics,
              std::unique_ptr<GraphicsComponent> graphics);
    ~GameActor() = default;

    [[nodiscard]] auto coordinates() -> Coordinates2D&;
    [[nodiscard]] auto coordinates() const -> const Coordinates2D&;
    [[nodiscard]] auto velocity() -> Velocity2D&;
    [[nodiscard]] auto velocity() const -> const Velocity2D&;

    void update() override;
    void render() const override;

private:
    std::unique_ptr<InputComponent> input_;
    std::unique_ptr<PhysicsComponent> physics_;
    std::unique_ptr<GraphicsComponent> graphics_;
    Coordinates2D coordinates_;
    Velocity2D velocity_;
};

} // namespace asteroids

#endif // ASTEROIDS_GAMEACTOR_H

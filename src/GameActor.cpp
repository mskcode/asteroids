#include "GameActor.h"

using namespace asteroids;

GameActor::GameActor(std::unique_ptr<InputComponent> input,
                     std::unique_ptr<PhysicsComponent> physics,
                     std::unique_ptr<GraphicsComponent> graphics) :
    input_(std::move(input)),
    physics_(std::move(physics)),
    graphics_(std::move(graphics)) {}

auto GameActor::coordinates() -> Coordinates2D& {
    return coordinates_;
}

auto GameActor::coordinates() const -> const Coordinates2D& {
    return coordinates_;
}

auto GameActor::velocity() -> Velocity2D& {
    return velocity_;
}

auto GameActor::velocity() const -> const Velocity2D& {
    return velocity_;
}

void GameActor::update() {
    input_->update(*this);
    physics_->update(*this);
}

void GameActor::render() const {
    graphics_->render(*this);
}

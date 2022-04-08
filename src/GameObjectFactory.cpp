#include "GameObjectFactory.h"
#include "KeyboardInputComponent.h"
#include "MoonPhysicsComponent.h"
#include <memory>

using namespace game;

GameObjectFactory::GameObjectFactory(const engine::Keyboard& keyboard,
                                     engine::ShaderProgramRegistry& shader_program_registry) :
    keyboard_(keyboard),
    shader_program_registry_(shader_program_registry) {}

auto GameObjectFactory::create_spaceship() -> GameActor* {
    auto input = std::make_unique<KeyboardInputComponent>(keyboard_);
    auto physics = std::make_unique<MoonPhysicsComponent>();

    auto r = std::make_unique<engine::RenderableObject<engine::Vertex3D, 3>>(shader_program_registry_, 0);
    auto graphics = std::make_unique<GraphicsComponent>(std::move(r));

    auto* obj = new GameActor(std::move(input), std::move(physics), std::move(graphics));
    objects_.push_back(obj);
    renderables_.push_back(obj);
    updateables_.push_back(obj);
    return obj;
}

auto GameObjectFactory::renderables() const -> const std::vector<Renderable*>& {
    return renderables_;
}

auto GameObjectFactory::updateables() const -> const std::vector<Updateable*>& {
    return updateables_;
}

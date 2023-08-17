#include "GameObjectFactory.h"
#include "KeyboardInputComponent.h"
#include "MoonPhysicsComponent.h"
#include "ResourceId.h"
#include "engine/Shader.h"
#include <memory>

using namespace game;

auto GameObjectFactory::create_spaceship() -> GameActor* {
    auto& keyboard = engine::Keyboard::instance();
    auto input = std::make_unique<KeyboardInputComponent>(keyboard);
    auto physics = std::make_unique<MoonPhysicsComponent>();

    auto texture = texture_registry_.load_texture(1, "./resources/images/smiley-256x256.png");

    auto shader_program = engine::ShaderProgramRegistry::instance().get((u32)ShaderProgramId::DEFAULT);

    auto r = std::make_unique<engine::RenderableObject>(shader_program, texture);
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

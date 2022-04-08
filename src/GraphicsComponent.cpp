#include "GraphicsComponent.h"
#include "GameActor.h"

using namespace asteroids;

static auto generate_vertex_data(const Coordinates2D& position) -> std::array<opengl::Vertex3D, 3> {
    constexpr opengl::VertexColor color{0.5f, 0.1f, 0.5f};
    return {{{{position.x - 0.2f, position.y - 0.2f, 0.0f}, color}, // bottom left
             {{position.x + 0.2f, position.y - 0.2f, 0.0f}, color}, // bottom right
             {{position.x, position.y + 0.2f, 0.0F}, color}}};      // top
}

GraphicsComponent::GraphicsComponent(std::unique_ptr<opengl::RenderableObject<opengl::Vertex3D, 3>> renderable_object) :
    renderable_object_(std::move(renderable_object)) {}

void GraphicsComponent::render(const GameActor& game_actor) {
    auto vertex_data = generate_vertex_data(game_actor.coordinates());
    // FIXME now we always update the data in GCU even when it hasn't changed
    renderable_object_->update_data(vertex_data);
    renderable_object_->render();
}

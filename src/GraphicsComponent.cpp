#include "GraphicsComponent.h"
#include "GameActor.h"

using namespace game;

static auto generate_vertex_data(const Coordinates2D& position) -> std::array<engine::Vertex, 8> {
    constexpr engine::Color color1{0.5f, 0.1f, 0.5f};
    constexpr engine::Color color2{0.1f, 0.5f, 0.5f};

    /*
    return {{{{position.x - 0.2f, position.y - 0.2f, 0.0f}, color}, // bottom left
             {{position.x + 0.2f, position.y - 0.2f, 0.0f}, color}, // bottom right
             {{position.x, position.y + 0.2f, 0.0F}, color}}};      // top
    */

    constexpr std::array<engine::TextureCoordinates, 8> texture_coordinates{{
        {0.0f, 0.0f}, // front, bottom, left
        {1.0f, 0.0f}, // front, bottom, right
        {1.0f, 1.0f}, // front, top, right
        {0.0f, 1.0f}, // front, top, left

        {0.0f, 0.0f}, // back, bottom, left
        {1.0f, 0.0f}, // back, bottom, right
        {1.0f, 1.0f}, // back, top, right
        {0.0f, 1.0f}, // back, top, left
    }};

    return {{
        {{position.x, position.y, 0.0f}, color1, texture_coordinates[0]},               // front, bottom, left
        {{position.x + 0.2f, position.y, 0.0f}, color1, texture_coordinates[0]},        // front, bottom, right
        {{position.x + 0.2f, position.y + 0.2f, 0.0f}, color1, texture_coordinates[0]}, // front, top, right
        {{position.x, position.y + 0.2f, 0.0f}, color1, texture_coordinates[0]},        // front, top, left

        {{position.x, position.y, -0.2f}, color2, texture_coordinates[0]},               // back, bottom, left
        {{position.x + 0.2f, position.y, -0.2f}, color2, texture_coordinates[0]},        // back, bottom, right
        {{position.x + 0.2f, position.y + 0.2f, -0.2f}, color2, texture_coordinates[0]}, // back, top, right
        {{position.x, position.y + 0.2f, -0.2f}, color2, texture_coordinates[0]},        // back, top, left
    }};
}

constexpr static auto generate_index_data() -> std::array<GLuint, 36> {
    return {
        1, 0, 3, 1, 3, 2, // north (-z)
        4, 5, 6, 4, 6, 7, // south (+z)
        5, 1, 2, 5, 2, 6, // east (+x)
        0, 4, 7, 0, 7, 3, // west (-x)
        2, 3, 7, 2, 7, 6, // top (+y)
        5, 4, 0, 5, 0, 1  // bottom (-y)
    };
}

GraphicsComponent::GraphicsComponent(std::unique_ptr<engine::RenderableObject> renderable_object) :
    renderable_object_(std::move(renderable_object)) {}

void GraphicsComponent::render(const GameActor& game_actor) {
    auto vertex_data = generate_vertex_data(game_actor.coordinates());
    auto index_data = generate_index_data();
    // FIXME now we always update the data in GPU even when it hasn't changed
    renderable_object_->vbo().set_data(vertex_data);
    renderable_object_->ebo().set_data(index_data);
    renderable_object_->render();
}

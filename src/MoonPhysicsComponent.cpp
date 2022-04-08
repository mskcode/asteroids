#include "MoonPhysicsComponent.h"
#include "GameActor.h"

using namespace asteroids;

void MoonPhysicsComponent::update(GameActor& game_actor) {
    game_actor.coordinates().x += game_actor.velocity().x_velocity;
    game_actor.coordinates().y += game_actor.velocity().y_velocity;
}

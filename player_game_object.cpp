#include "player_game_object.h"
#include <iostream>
namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture)
	: GameObject(position, geom, shader, texture) {
    oType = Player;
    maxVelocity_ = 5;
}

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {

    // TODO MAKE FEEL BETTER, TWEEK VALUES
    if (glm::length(velocity_) > 2.0f) {
        velocity_ -= velocity_ * 1.75f * glm::vec3(delta_time);
    } else if (glm::length(velocity_) < 0.5f && !accelerating) {
        velocity_ = glm::vec3(0.0f, 0.0f, 0.0f);
    } else if ((glm::length(velocity_) < 2.0f)) {
        velocity_ -= velocity_ * 0.9f * glm::vec3(delta_time);
    }

	// Call the parent's update method to move the object in standard way, if desired
	GameObject::Update(delta_time);
}
} // namespace game

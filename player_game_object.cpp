#include "player_game_object.h"

namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture)
	: GameObject(position, geom, shader, texture) {
    oType = Player;
}

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {

    // and friction and set velocity to 0 if it becomes very small
    if (glm::length(velocity_) > 2.0f) {
        velocity_ -= velocity_ * 0.005f;
    } else if ((glm::length(velocity_) < 2.0f)) {
        velocity_ -= velocity_ * 0.002f;
    } else if (glm::length(velocity_) < 0.02f) {
        velocity_ = glm::vec3(0.0f, 0.0f, 0.0f);
    }

	// Call the parent's update method to move the object in standard way, if desired
	GameObject::Update(delta_time);
}

} // namespace game

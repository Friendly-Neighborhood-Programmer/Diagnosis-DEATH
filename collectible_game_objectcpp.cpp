#include "collectible_game_object.h"

namespace game {

	// collectible object constructor
	CollectibleGameObject::CollectibleGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
		: GameObject(position, geom, shader, texture) {
		oType = Collectible;
	}

	// update function to be called each frame
	void CollectibleGameObject::Update(double delta_time) {

		// Special collectible updates go here

		// Call the parent's update method to move the object in standard way, if desired
		GameObject::Update(delta_time);
	}

}
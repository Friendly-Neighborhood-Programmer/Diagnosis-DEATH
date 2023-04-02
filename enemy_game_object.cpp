#include "enemy_game_object.h"
#include <iostream>

namespace game {

// enemy object constructor
EnemyGameObject::EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
    : GameObject(position, geom, shader, texture) { 
    oType = Enemy;
}

// update function to be called each frame
void EnemyGameObject::Update(double delta_time, glm::vec3 pos) {
}

} // namespace game
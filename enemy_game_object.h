#ifndef ENEMY_OBJECT_H
#define ENEMY_OBJECT_H

#include "game_object.h"

namespace game {

    class EnemyGameObject : public GameObject {

    public:

        EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

        // Update function for moving the player object around
        void Update(double delta_time, glm::vec3);

    };


} // namespace game

#endif // COLLECTIBLE_OBJECT_H
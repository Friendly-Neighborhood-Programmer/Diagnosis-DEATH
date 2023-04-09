#include "enemy_bullet_game_object.h"

namespace game {


    EnemyBulletGameObject::EnemyBulletGameObject(glm::vec3 position, float angle, glm::vec3 bearing, Geometry* geom, Shader* shader, GLuint texture)
        : BulletGameObject(position, geom, shader, texture) {
        bType = Enemy;;
        speed = 5.0f;
        SetScale(0.8);
        SetAngle(angle);
        SetVelocity(bearing * speed);
        hitsEnemies = false;
        hitsPlayers = true;
    }

    // Update function for moving the player object around
    void EnemyBulletGameObject::Update(double delta_time) {
        //if (lifetime >= 1.0f) { state_ = Exploded; }

        // Call the parent's update method to move the object in standard way, if desired
        BulletGameObject::Update(delta_time);
    }


} // namespace game
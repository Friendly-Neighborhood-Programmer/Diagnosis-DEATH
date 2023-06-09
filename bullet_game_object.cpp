#include "bullet_game_object.h"
#include <iostream>
namespace game {

    /*
        PlayerGameObject inherits from GameObject
        It overrides GameObject's update method, so that you can check for input to change the velocity of the player
    */

    BulletGameObject::BulletGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
        : GameObject(position, geom, shader, texture) {
        oType = Bullet;
        bType = Generic;
        speed = 1.0f;
    }

    // Update function for moving the player object around
    void BulletGameObject::Update(double delta_time) {
        //if (lifetime >= 1.0f) { state_ = Exploded; }

        // Call the parent's update method to move the object in standard way, if desired
        GameObject::Update(delta_time);
    }

    BulletGameObject::BulletType BulletGameObject::getBulletType() {
        return bType;
    }
    void BulletGameObject::setSpeed(float s) { speed = s; }
    float BulletGameObject::getSpeed() { return speed; }
    void BulletGameObject::die() { bulletDie(); }
    void BulletGameObject::bulletDie() { 
        state_ = DyingBullet; 
        speed *= 0.1;
        SetVelocity(GetVelocity() * speed);
        if (particle != nullptr) {
            particle->die();
        }
    }

} // namespace game
#include "player_game_object.h"
#include <iostream>
#include "player_bullet_game_object.h"
#include <glm/gtc/matrix_transform.hpp>
namespace game {

/*
	PlayerGameObject inherits from GameObject
	It overrides GameObject's update method, so that you can check for input to change the velocity of the player
*/

PlayerGameObject::PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture)
	: GameObject(position, geom, shader, texture) {
    oType = Player;
    maxVelocity_ = 5;
    spiralShotAmt = 10;
    damageTimer = 0;
}

// Update function for moving the player object around
void PlayerGameObject::Update(double delta_time) {
    time += delta_time;
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

BulletGameObject* PlayerGameObject::shoot(Geometry* sprite, Shader* shader, GLuint texture) {
    BulletGameObject* bullet = new PlayerBulletGameObject(position_, angle_, GetBearing(), sprite, shader, texture);
    bullet->setDamage(getDamage());
    return bullet;
}

int PlayerGameObject::dealDamage() {
    if (damageTimer <= time) {
        damageTimer = time + 0.75;
        return damage;
    }
    return 0;
}

vector<PlayerBulletGameObject*> PlayerGameObject::spiralShoot(Geometry* sprite, Shader* shader, GLuint texture, int numScales) {
    bulletAmount--;
    vector<PlayerBulletGameObject*> bullets;

    for (int i = 0; i < spiralShotAmt; i++) {
        float angle = angle_ + glm::radians(360.f / spiralShotAmt * i);
        glm::vec3 dir = glm::vec3(glm::cos(angle), glm::sin(angle), 0);

        PlayerBulletGameObject* bullet = new PlayerBulletGameObject(position_, angle-glm::radians(90.f), dir, sprite, shader, texture);
        bullet->setDamage(2);
        bullet->SetScale(2 + ((numScales * 0.5)));
        
        //add to collection of all bullets
        bullets.push_back(bullet);
    }

    return bullets;
}
} // namespace game

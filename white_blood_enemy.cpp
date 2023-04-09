#include "white_blood_enemy.h"
#include "enemy_bullet_game_object.h"
#include <glm/gtc/matrix_transform.hpp>

namespace game {
    WhiteBloodEnemy::WhiteBloodEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
        : EnemyGameObject(position, geom, shader, texture) {
        radius = 0.5f;
        curHealth = 7;
        damage = 2;
        speed = 0.7f;
        bulletSprite = nullptr;
        bulletTexture = nullptr;
        bulletShader = nullptr;
        attackTimer = 0;
        setTimer();
    }

    //init bullet things :)
    void WhiteBloodEnemy::init(Geometry* s, GLuint* t, Shader* sh, Game* g) {
        bulletSprite = s;
        bulletTexture = t;
        bulletShader = sh;
        game = g;
    }

    void WhiteBloodEnemy::Update(double delta_time) {
        time += delta_time;
        //detect if player is close
        if (target != nullptr) {
            float distance = glm::length(position_ - target->GetPosition());
            state = Patrolling;

            if (distance < 6.0f) {
                state = Moving;
            }
            if (distance < 4.0f) {
                state = Attacking;
            }
            if (distance < 1.8f) {
                state = Running;
            }

            EnemyGameObject::Update(delta_time);
        }
    }

    //attack cooldown, with a little randomness
    void WhiteBloodEnemy::setTimer() {
        attackTimer = time + 2 + randF(-1.0f, 1.0f);
    }

    //move towards player, with a little randomness
    void WhiteBloodEnemy::move(double delta_time) {
        position_ -= glm::normalize((position_ - ((target->GetPosition() + glm::vec3(randF(-1.0f, 1.0f), randF(-1.0f, 1.0f), 0))))) * ((float)delta_time) * speed;
    }

    void WhiteBloodEnemy::attack(double delta_time) {
        if (attackTimer <= time) {
            glm::vec3 direction = glm::normalize(target->GetPosition() - GetPosition());
            float angle = angle_;
            angle = (glm::atan(direction.y / direction.x));
            angle += (glm::pi<float>() / 2); //Uneeded, but might be useful later
            EnemyBulletGameObject* bullet = new EnemyBulletGameObject(position_, angle, direction, bulletSprite, bulletShader, *bulletTexture);
            bullet->setDamage(getDamage());
            game->addGameObject(bullet);
            setTimer();
        }
        if (moveTimer <= time) {
            randPoint = glm::vec3(randF(-10.0f, 10.0f), randF(-10.0f, 10.0f), 0.0f);
            randPoint = glm::normalize(randPoint);
            moveTimer = time + 0.75f + randF(-0.25f, 0.25f);
        }
        position_ -= randPoint * (float)delta_time * speed;
    }
}
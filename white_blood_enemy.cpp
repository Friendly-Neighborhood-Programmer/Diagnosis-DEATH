#include "white_blood_enemy.h"

namespace game {
    WhiteBloodEnemy::WhiteBloodEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
        : EnemyGameObject(position, geom, shader, texture) {
        radius = 0.5f;
        curHealth = 7;
    }

    void WhiteBloodEnemy::Update(double delta_time) {
        time += delta_time;
        //detect if player is close
        if (target != nullptr) {
            float distance = glm::length(position_ - target->GetPosition());
            state = Patrolling;

            if (distance < 4.0f) {
                state = Moving;
            }
            if (distance < 2.0f) {
                state = Attacking;
            }
            if (distance < 1.0f) {
                state = Running;
            }

            EnemyGameObject::Update(delta_time);
        }
    }

    void WhiteBloodEnemy::move(double delta_time) {}
    void WhiteBloodEnemy::attack(double delta_time) {}
}
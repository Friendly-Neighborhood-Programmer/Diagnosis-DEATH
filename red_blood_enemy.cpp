#include "red_blood_enemy.h"
#define CHARGE_SPEED 3
#include <iostream>


namespace game {
    RedBloodEnemy::RedBloodEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
        : EnemyGameObject(position, geom, shader, texture) {
        radius = 1.0f;
        attackTimer = -1.0;
        curHealth = 3;
    }

    void RedBloodEnemy::Update(double delta_time) {
        time += delta_time;
        //detect if player is close
        if (target != nullptr && state != Charge) {
            float distance = glm::length(position_ - target->GetPosition());
            if (distance > 3.0f) {
                state = Patrolling;
            }
            else if (distance < 2 || state == Attacking) {
                if (state != Attacking) {
                    startAttack();
                }
                state = Attacking;
            }
            else if (distance < 3.0f) {
                state = Moving;
            }
        }
            
        if (state == Charge) {
            charge(delta_time);
        }

        EnemyGameObject::Update(delta_time);
    }

    void RedBloodEnemy::attack(double delta_time) {
        if (attackTimer <= time) {
            chargePoint = position_ - target->GetPosition();
            state = Charge;
        }
    }

    void RedBloodEnemy::move(double delta_time) {
        position_ -= glm::normalize((position_ - (target->GetPosition() * glm::vec3(2, 2, 1)))) * ((float)delta_time);
    }

    void RedBloodEnemy::charge(double delta_time) {
        position_ -= glm::normalize((chargePoint)) * ((float)delta_time) * glm::vec3(CHARGE_SPEED, CHARGE_SPEED, 0);
        if ((attackTimer + 1) <= time) {
            //stop charging
            state = Patrolling;
        }
    }

    void RedBloodEnemy::startAttack() {
        attackTimer = time + 1.2;
    }
}
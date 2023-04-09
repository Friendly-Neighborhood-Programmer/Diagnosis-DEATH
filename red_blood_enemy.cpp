#include "red_blood_enemy.h"
#include <iostream>
#define CHARGE_SPEED 4
#define PLAYER_RANGE 3
#define START_CHARGE_RANGE 2


namespace game {
    RedBloodEnemy::RedBloodEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
        : EnemyGameObject(position, geom, shader, texture) {
        radius = 1.0f;
        attackTimer = -1.0;
        curHealth = 3;
        speed = 1.4f;
        damage = 1;
    }

    void RedBloodEnemy::Update(double delta_time) {
        time += delta_time;
        //detect if player is close
        if (target != nullptr && state != Charge) {
            float distance = glm::length(position_ - target->GetPosition());
            if (distance > PLAYER_RANGE) {
                //not close, so patrol
                state = Patrolling;
            }
            //if in middle of attacking or need to start attacking
            else if (distance < START_CHARGE_RANGE || state == Attacking) {
                if (state != Attacking) {
                    startAttack();
                }
                state = Attacking;
            }
            //else means walk towards player
            else if (distance < PLAYER_RANGE) {
                state = Moving;
            }
        }
            
        if (state == Charge) {
            charge(delta_time);
        }

        EnemyGameObject::Update(delta_time);
    }

    //attack, meaning start charging
    void RedBloodEnemy::attack(double delta_time) {
        if (attackTimer <= time) {
            chargePoint = position_ - target->GetPosition();
            state = Charge;
        }
    }

    //move towards player, with a little randomness
    void RedBloodEnemy::move(double delta_time) {
        position_ -= glm::normalize((position_ - ((target->GetPosition() * glm::vec3(2, 2, 1) + glm::vec3(randF(-1.0f, 1.0f), randF(-1.0f, 1.0f), 0))))) * ((float)delta_time) * speed;
    }

    //charge towards charge point, which is players position 1.2 seconds ago
    void RedBloodEnemy::charge(double delta_time) {
        position_ -= glm::normalize((chargePoint)) * ((float)delta_time) * glm::vec3(CHARGE_SPEED, CHARGE_SPEED, 0);
        if ((attackTimer + 1) <= time) {
            //stop charging after 1 second
            state = Patrolling;
        }
    }

    //will start charging towards point in 1.2 seconds
    void RedBloodEnemy::startAttack() {
        attackTimer = time + 1.2;
    }
}
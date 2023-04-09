#include "enemy_game_object.h"
#include <iostream>
using namespace std;
namespace game {

    // enemy object constructor
    EnemyGameObject::EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
        : GameObject(position, geom, shader, texture) {
        oType = Enemy;
        state = Patrolling;
        time = 0.0f;
        target = nullptr;
        radius = 0;
        damageTimer = 0;
        hitsEnemies = false;
        hitsPlayers = true;
        moveTimer = 0;
    }

    int EnemyGameObject::dealDamage() {
        if (damageTimer <= time) {
            damageTimer = time + 1;
            return damage;
        }
        return 0;
    }

    // update function to be called each frame
    void EnemyGameObject::Update(double delta_time) {
        time += delta_time;
        //detect if player is close
        if(target != nullptr){
            // Special collectible updates go here
            if (state == Patrolling) {
                // circle around startPoint
                patrol(delta_time);
            }
            else if (state == Moving) {
                // move to player
                move(delta_time);
            }
            else if (state == Attacking) {
                attack(delta_time);
            }
            else if (state == Running) {
                run(delta_time);
            }
        }  
    }

    void EnemyGameObject::run(double delta_time) {
        position_ -= (target->GetPosition() - position_) * ((float)delta_time);
    }

    void EnemyGameObject::patrol(double delta_time) {
        if (moveTimer <= time) {
            randPoint = glm::vec3(randF(-10.0f, 10.0f), randF(-10.0f, 10.0f), 0.0f);
            randPoint = glm::normalize(randPoint);
            moveTimer = time + 2;
        }
        position_ -= randPoint * (float)delta_time;
    }

    void EnemyGameObject::setTarget(GameObject* g) {
        target = g;
    }

    void EnemyGameObject::setRadius(float f) {
        radius = f;
    }

    float EnemyGameObject::randF(float min, float max) {
        return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
    }

} // namespace game
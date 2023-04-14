#pragma once
#ifndef RED_BLOOD_ENEMY_H
#define RED_BLOOD_ENEMY_H

#include "enemy_game_object.h"

namespace game {

    class RedBloodEnemy : public EnemyGameObject {

    public:
        RedBloodEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
        // Update function for moving the player object around
        virtual void Update(double delta_time);
        virtual void attack(double);
        virtual void move(double);
        virtual void charge(double);

    protected:
        void startAttack();
        double attackTimer;
        glm::vec3 chargePoint;
        glm::vec3 randPoint;
        double moveTimer;
    };


} // namespace game

#endif // RED_BLOOD_ENEMY_H

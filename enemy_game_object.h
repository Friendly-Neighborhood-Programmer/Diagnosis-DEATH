#ifndef ENEMY_OBJECT_H
#define ENEMY_OBJECT_H

#include "game_object.h"

namespace game {

    class EnemyGameObject : public GameObject {

    public:
        enum State { Patrolling, Moving, Attacking, Running, Charge};

        EnemyGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
        // Update function for moving the player object around
        virtual void Update(double delta_time);
        //time that has passed since the start of the program
        double time;
        virtual void attack(double) = 0;
        virtual void move(double) = 0;
        virtual void patrol(double);
        virtual void run(double);
        virtual int dealDamage();
        void setTarget(GameObject*);
        void setRadius(float);

    protected:

        State state;
        // centre of the patrol circle
        glm::vec3 randPoint;
        GameObject* target;
        float radius;
        double damageTimer;
        double moveTimer;
        float randF(float, float);

    };


} // namespace game

#endif // ENEMY_GAME_OBJECT_H
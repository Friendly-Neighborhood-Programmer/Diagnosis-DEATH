#pragma once
#ifndef WHITE_BLOOD_ENEMY_H
#define WHITE_BLOOD_ENEMY_H
#include "game.h"
#include "shader.h"
#include "sprite.h"

#include "enemy_game_object.h"

namespace game {

    class WhiteBloodEnemy : public EnemyGameObject {

    public:
        WhiteBloodEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
        // Update function for moving the player object around
        virtual void Update(double delta_time);
        virtual void attack(double);
        virtual void move(double);
        void init(Geometry*, GLuint*, Shader*, Game*);

    protected:
        void setTimer();
        Geometry* bulletSprite;
        GLuint* bulletTexture;
        Shader* bulletShader;
        Game* game;
        double attackTimer;
    };


} // namespace game

#endif // WHITE_BLOOD_ENEMY_H

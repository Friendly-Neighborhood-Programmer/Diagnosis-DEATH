#pragma once
#ifndef STEM_CELL_ENEMY_H
#define STEM_CELL_ENEMY_H
#include "shader.h"
#include "sprite.h"
#include "enemy_game_object.h"
#include "game.h"

namespace game {

    class StemCellEnemy : public EnemyGameObject {

    public:
        StemCellEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);
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

#endif // STEM_CELL_ENEMY_H
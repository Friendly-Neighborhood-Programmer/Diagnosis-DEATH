#include "stem_cell_enemy.h"

#include "enemy_bullet_game_object.h"
#include <glm/gtc/matrix_transform.hpp>

#define NUM_BULLETS 6

namespace game {
    StemCellEnemy::StemCellEnemy(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture)
        : EnemyGameObject(position, geom, shader, texture) {
        radius = 0.0f;
        state = Attacking;
        bulletSprite = nullptr;
        bulletTexture = nullptr;
        bulletShader = nullptr;
        setTimer();
        curHealth = 15;
        damage = 1;
    }

    //attack cooldown, with a little randomness
    void StemCellEnemy::setTimer() {
        attackTimer = time + 3 + randF(-1.0f, 2.0f);
    }

    void StemCellEnemy::Update(double delta_time) {
        time += delta_time;
        //detect if player is close
        if (target != nullptr) {
            //will basically just call attack() since my state is always attack
            EnemyGameObject::Update(delta_time);
        }
    }

    //init bullet things :)
    void StemCellEnemy::init(Geometry* s, GLuint* t, Shader* sh, Game* g) {
        bulletSprite = s;
        bulletTexture = t;
        bulletShader = sh;
        game = g;
    }

    //shoot bullets in a circle
    void StemCellEnemy::attack(double delta_time) {
        if(attackTimer <= time){
            glm::vec3 direction = glm::vec3(0);
            float angle = angle_;
            for (int i = 0; i < NUM_BULLETS; i++) {
                direction.x = glm::cos((float)i);
                direction.y = glm::sin((float)i);
                direction = glm::normalize(direction);
                angle = (glm::atan(direction.y / direction.x));
                angle += (glm::pi<float>() / 2); //Uneeded, but might be useful later
                EnemyBulletGameObject* bullet = new EnemyBulletGameObject(position_, angle, direction, bulletSprite, bulletShader, *bulletTexture);
                bullet->setDamage(getDamage());
                game->addGameObject(bullet);
            }
            setTimer();
        }    
    }
    void StemCellEnemy::move(double delta_time) {}
}
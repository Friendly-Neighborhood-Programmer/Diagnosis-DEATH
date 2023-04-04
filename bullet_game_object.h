#ifndef BULLET_H
#define BULLET_H

#include "game_object.h"

namespace game {

    // Inherits from GameObject
    class BulletGameObject : public GameObject {

        public:
            BulletGameObject(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture);

            // Update function for moving the player object around
            void Update(double delta_time) override;
            enum BulletType{Generic, Player};
            BulletType bType;

            float getSpeed();
            void setSpeed(float);
    protected:
        float speed;
        
    }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_

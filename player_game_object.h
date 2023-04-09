#ifndef PLAYER_GAME_OBJECT_H_
#define PLAYER_GAME_OBJECT_H_

#include "game_object.h"
#include <vector>
using namespace std;
namespace game {
    class PlayerBulletGameObject;
    // Inherits from GameObject
    class PlayerGameObject : public GameObject {

        public:
            PlayerGameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture);

            // Update function for moving the player object around
            void Update(double delta_time) override;
            virtual BulletGameObject* shoot(Geometry* geom, Shader* shader, GLuint texture);
            vector<PlayerBulletGameObject*> spiralShoot(Geometry* sprite, Shader* shader, GLuint texture);
            virtual int dealDamage();
            double time;

    protected:
        int spiralShotAmt;
        double damageTimer;

    }; // class PlayerGameObject

} // namespace game

#endif // PLAYER_GAME_OBJECT_H_

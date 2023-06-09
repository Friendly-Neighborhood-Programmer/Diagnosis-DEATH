#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>

#include "shader.h"
#include "geometry.h"
#include <vector>
using namespace std;
namespace game {
    class BulletGameObject;
    /*
        GameObject is responsible for handling the rendering and updating of one object in the game world
        The update and render methods are virtual, so you can inherit them from GameObject and override the update or render functionality (see PlayerGameObject for reference)
    */
    class GameObject {

        public:
            enum State { Active, Exploded, Died, DyingBullet };

            //KEEP COLLECTIBLE AND ON AS THE LAST 4 IN THIS ENUM
            enum ObjectType { Player, Enemy, Bullet, Particles, Blade, Collectible, Bacteria, Fat, Germ, UI};

            // Constructor
            GameObject(const glm::vec3 &position, Geometry *geom, Shader *shader, GLuint texture);

            // Update the GameObject's state. Can be overriden in children
            virtual void Update(double delta_time);

            // Renders the GameObject 
            virtual void Render(glm::mat4 view_matrix, double current_time);

            virtual void die();

            virtual void takeDamage(int);
            virtual int dealDamage();
            bool getHitsEnemies();
            bool getHitsPlayers();

            // Getters
            inline glm::vec3& GetPosition(void) { return position_; }
            inline float GetScale(void) { return scale_; }
            inline float GetAngle(void) { return angle_; }
            inline glm::vec3& GetVelocity(void) { return velocity_; }
            inline State GetState(void) { return state_; }
            inline ObjectType getType() { return oType; }
            virtual int getDamage() { return damage; };
            int getScore() { return score; }

            // Get bearing direction (direction in which the game object
            // is facing)
            glm::vec3 GetBearing(void);

            // Get vector pointing to the right side of the game object
            glm::vec3 GetRight(void);

            // Setters
            inline void SetPosition(const glm::vec3& position) { position_ = position; }
            inline void SetScale(float scale) { scale_ = scale; }
            void SetAngle(float angle);
            void SetParent(GameObject*);
            void setType(ObjectType type) { oType = type; }
            void setDamage(int amount) { damage = amount; }
            void setMaxHealth(int newHealth) { maxHealth = newHealth; }
            int getMaxHealth() { return maxHealth; }
            int getHealth() { return curHealth; }
            virtual void setChildParticle(GameObject* newP) { particle = newP; };
            virtual GameObject* getChildParticle() { return particle; };
            virtual void setBullet(GameObject* newBullet) { bullet = newBullet; }

            virtual void SetVelocity(const glm::vec3& velocity);

            virtual void heal(int amount);

            float timeAlive;
            void Explode(GLuint exp_texture);

            bool canShoot();
            virtual BulletGameObject* shoot(Geometry* geom, Shader* shader, GLuint texture);

            bool isColliding(GameObject *other);

            void setAccelerating(const bool);

            void addBulletAmount(int amount) { bulletAmount += amount; }
            void removeBulletAmount(int amount) { bulletAmount -= amount; }
            int getBulletAmount() { return bulletAmount; }

            void setIsMainPlayer(bool mp) { isMainPlayer = mp; }
            bool getIsMainPlayer() { return isMainPlayer; }
            bool isUi() { return oType == UI; }

        protected:
            bool hitsEnemies;
            bool hitsPlayers;
            //proporties
            float maxVelocity_;
            bool accelerating;
            float cooldown;
            // Object's Transform Variables
            glm::vec3 position_;
            float scale_;
            float angle_;
            glm::vec3 velocity_;

            // Geometry
            Geometry *geometry_;
 
            // Shader
            Shader *shader_;

            // Object's texture reference
            GLuint texture_;

            // Explosion handling
            State state_;
            float exp_time_;
            float exp_end_time_;

            // added enum to identify the object type
            ObjectType oType;
            bool isMainPlayer;
            // Cooldown for firing bullets
            float shotCooldown;

            glm::vec3 startPos;

            GameObject *parent;
            int damage;
            int maxHealth;
            int curHealth;

            GameObject* particle;

            GameObject* bullet;
            int bulletAmount;

            int score;

    }; // class GameObject

} // namespace game

#endif // GAME_OBJECT_H_

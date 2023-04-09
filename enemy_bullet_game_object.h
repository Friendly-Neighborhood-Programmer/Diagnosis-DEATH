#ifndef ENEMY_BULLET_GAME_OBJECT
#define ENEMY_BULLET_GAME_OBJECT
#include "bullet_game_object.h"
#include "game_object.h"
namespace game {
	class EnemyBulletGameObject : public BulletGameObject {
	public:
		EnemyBulletGameObject(glm::vec3, float, glm::vec3, Geometry*, Shader*, GLuint);
		virtual void Update(double delta_time);
	};
}
#endif

#ifndef PLAYER_BULLET_GAME_OBJECT
#define PLAYER_BULLET_GAME_OBJECT
#include "bullet_game_object.h"
#include "game_object.h"
#include "player_game_object.h"
namespace game {
	class PlayerBulletGameObject : public BulletGameObject {
	public:
		PlayerBulletGameObject(glm::vec3 position, float angle, glm::vec3 bearing, Geometry* geom, Shader* shader, GLuint texture);
		virtual void Update(double delta_time);
	};
}
#endif
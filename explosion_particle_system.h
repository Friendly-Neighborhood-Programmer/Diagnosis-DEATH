#ifndef EXPLOSION_PARTICLE_SYSTEM_H_
#define EXPLOSION_PARTICLE_SYSTEM_H_

#include "particle_system.h"

namespace game {

    // Inherits from GameObject
    class ExplosionParticleSystem : public ParticleSystem {

    public:
        ExplosionParticleSystem(const glm::vec3& position, Geometry* geom, Shader* shader, GLuint texture, GameObject* parent);

        void Update(double delta_time) override;

        void Render(glm::mat4 view_matrix, double current_time);

    private:
        float timeActive;

    }; // class ParticleSystem

} // namespace game

#endif // PARTICLE_SYSTEM_H_
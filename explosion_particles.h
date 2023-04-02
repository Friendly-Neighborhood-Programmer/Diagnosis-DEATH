#ifndef EXPLOSION_PARTICLES_H_
#define EXPLOSION_PARTICLES_H_

#include "particles.h"

namespace game {

    // A set of particles that can be rendered
    class ExplosionParticles : public Particles {

        public:
            ExplosionParticles(void);

            // Create the geometry (called once)
            void CreateGeometry(void);

    }; // class Particles
} // namespace game

#endif // EXPLOSION_PARTICLES_H_

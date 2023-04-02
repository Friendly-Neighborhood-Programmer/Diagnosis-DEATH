#ifndef TRAIL_PARTICLES_H_
#define TRAIL_PARTICLES_H_

#include "particles.h"

namespace game {

    // A set of particles that can be rendered
    class TrailParticles : public Particles {

    public:
        TrailParticles(void);

        // Create the geometry (called once)
        void CreateGeometry(void);

    }; // class Particles
} // namespace game

#endif // EXPLOSION_PARTICLES_H_
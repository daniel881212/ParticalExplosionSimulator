//
// Created by Daniel Chen on 2020-02-27.
//

#ifndef PARTICALEXPLOSIONSIMULATOR_SWARM_H
#define PARTICALEXPLOSIONSIMULATOR_SWARM_H

#include "Particle.h"

namespace ParticleExplosionProject {
    class Swarm {
    public:
        const static int NPARTICLES = 5000;

    private:
        Particle *m_pParticles;
        int lastTime;

    public:
        Swarm();
        virtual ~Swarm();
        Particle * const getParticles() { return m_pParticles; }
        void update(int elapsed);
    };
}


#endif //PARTICALEXPLOSIONSIMULATOR_SWARM_H

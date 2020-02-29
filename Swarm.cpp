//
// Created by Daniel Chen on 2020-02-27.
//

#include "Swarm.h"

namespace ParticleExplosionProject {
    Swarm::Swarm(): lastTime(0) {
        m_pParticles = new Particle[NPARTICLES];
    }

    Swarm::~Swarm() {
        delete [] m_pParticles;
    }

    void Swarm::update(int elapsed) {
        int timeInterval = elapsed - lastTime;

        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            m_pParticles[i].update(timeInterval);
        }

        lastTime = elapsed;
    }
}
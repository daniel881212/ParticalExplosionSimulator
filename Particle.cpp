//
// Created by Daniel Chen on 2020-02-27.
//

#include "Particle.h"
#include <math.h>
#include <stdlib.h>

namespace ParticleExplosionProject{
    Particle::Particle() {
        init();
    }

    Particle::~Particle() {

    }

    void Particle::update(int timeInterval) {
        m_angle += timeInterval * 0.0004;

        double x_speed = m_speed * cos(m_angle);
        double y_speed = m_speed * sin(m_angle);

        m_x += x_speed * timeInterval;
        m_y += y_speed * timeInterval;

        if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) {
            init();
        }

        if (rand() < RAND_MAX / 100) {
            init();
        }
    }

    void Particle::init() {
        m_x = 0;
        m_y = 0;

        m_angle = (2 * M_PI * rand()) / RAND_MAX;
        m_speed = (0.02 * rand()) / RAND_MAX;

        m_speed *= m_speed;
    }
}

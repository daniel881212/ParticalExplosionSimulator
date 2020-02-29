//
// Created by Daniel Chen on 2020-02-27.
//

#ifndef PARTICALEXPLOSIONSIMULATOR_PARTICLE_H
#define PARTICALEXPLOSIONSIMULATOR_PARTICLE_H

namespace ParticleExplosionProject{
    struct Particle {
        double m_x;
        double m_y;

    private:
        double m_speed;
        double m_angle;

    public:
        Particle();
        virtual ~Particle();
        void update(int timeInterval);

    private:
        void init();
    };
}

#endif //PARTICALEXPLOSIONSIMULATOR_PARTICLE_H

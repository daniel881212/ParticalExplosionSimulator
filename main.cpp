#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"
#include "Particle.h"

using namespace std;
using namespace ParticleExplosionProject;

int main() {

    Screen screen;

    srand(time(NULL));

    if (!screen.init()) {
        cout << "Error Initializing SDL" << endl;
    }

    Swarm swarm;

    while (true) {
        // Update particle
        int elapsed = SDL_GetTicks();
        swarm.update(elapsed);

        unsigned char red = (1 + sin(elapsed * 0.00085)) * 128;
        unsigned char green = (1 + sin(elapsed * 0.00105)) * 128;
        unsigned char blue = (1 + sin(elapsed * 0.0005)) * 128;
        // Draw particle

        const Particle * const pParticle = swarm.getParticles();
        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticle[i];

            int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
            int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT / 2;

            screen.setPixel(x, y, red, green, blue);
        }

        screen.boxBlur();

        screen.update();

        if (!screen.processEvents()) {
            break;
        }
    }

    screen.close();

    return 0;
}

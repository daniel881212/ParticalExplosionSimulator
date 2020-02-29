//
// Created by Daniel Chen on 2020-02-27.
//

#ifndef PARTICALEXPLOSIONSIMULATOR_SCREEN_H
#define PARTICALEXPLOSIONSIMULATOR_SCREEN_H

#include "SDL.h"

namespace ParticleExplosionProject {
    class Screen {
    public:
        const static int SCREEN_WIDTH = 800;
        const static int SCREEN_HEIGHT = 600;

    private:
        SDL_Window *m_window;
        SDL_Texture *m_texture;
        SDL_Renderer *m_renderer;
        Uint32 *m_buffer1;
        Uint32 *m_buffer2;

    public:
        Screen();
        bool init();
        void update();
        void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
        static bool processEvents();
        void close();
        void boxBlur();
    };
}

#endif //PARTICALEXPLOSIONSIMULATOR_SCREEN_H

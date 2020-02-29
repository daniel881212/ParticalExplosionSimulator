//
// Created by Daniel Chen on 2020-02-27.
//
#include <iomanip>
#include <iostream>
#include <inttypes.h>
#include "Screen.h"

using namespace std;

namespace ParticleExplosionProject{
    Screen::Screen(): m_window(NULL), m_texture(NULL), m_renderer(NULL), m_buffer1(NULL), m_buffer2(NULL){

    }

    bool Screen::init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            cout << "Fail to initialize SDL." << endl;
            return false;
        }

        m_window = SDL_CreateWindow("Particle Fire Explosion",
                                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

        if (m_window == NULL) {
            SDL_Quit();
            return false;
        }

        m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
        m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC,
                                                 SCREEN_WIDTH, SCREEN_HEIGHT);

        if (m_renderer == NULL) {
            cout << "Couldn't create renderer." << flush;
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        if (m_texture == NULL) {
            cout << "Couldn't create texture." << flush;
            SDL_DestroyRenderer(m_renderer);
            SDL_DestroyWindow(m_window);
            SDL_Quit();
            return false;
        }

        m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
        m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
        memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
        memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

        return true;
    }

    void Screen::update() {
        SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }

    void Screen::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
        if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
            return;
        }

        uint8_t alpha = 0xFF;
        uint32_t colour = (red << 24) | (green << 16) | (blue << 8) | alpha;

        m_buffer1[(y * SCREEN_WIDTH) + x] = colour;
    }

    bool Screen::processEvents() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;
            }
        }
        return true;
    }

    void Screen::close() {
        delete [] m_buffer1;
        delete [] m_buffer2;
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyTexture(m_texture);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
    }

    void Screen::boxBlur() {
        // Swap the buffer so pixels are in buffer2 and we are drawing buffer1
        Uint32 *temp = m_buffer1;
        m_buffer1 = m_buffer2;
        m_buffer2 = temp;

        for (int y = 0; y < SCREEN_HEIGHT; y++) {
            for (int x = 0; x < SCREEN_WIDTH; x++) {
                /*
                 * 0 0 0
                 * 0 1 0
                 * 0 0 0
                 */
                int redTotal = 0;
                int greenTotal = 0;
                int blueTotal = 0;

                for (int row = -1; row <= 1; row++) {
                    for (int col = -1; col <= 1; col++) {
                        int currentX = x + col;
                        int currentY = y + row;

                        if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
                            Uint32 colour = m_buffer2[(currentY * SCREEN_WIDTH) + currentX];
                            Uint8 red = colour >> 24;
                            Uint8 green = colour >> 16;
                            Uint8 blue = colour >> 8;

                            redTotal += red;
                            greenTotal += green;
                            blueTotal += blue;
                        }
                    }

                    Uint8 red = redTotal / 9;
                    Uint8 green = greenTotal / 9;
                    Uint8 blue = blueTotal / 9;

                    setPixel(x, y, red, green, blue);
                }
            }
        }
    }
}


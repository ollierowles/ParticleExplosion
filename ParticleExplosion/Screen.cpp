#include "Screen.h"

namespace sdl_components {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL),m_buffer(NULL), m_buffer2(NULL) {
}


bool Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    m_window = SDL_CreateWindow("Particle Fire Explosion",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (m_window == NULL) {
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (m_renderer == NULL) {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    if (m_texture == NULL) {
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    // Allocating 32 bits per pixel for the window in memory
    m_buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
    m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

    // Writing pixel information into the buffer
    memset(m_buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
    memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

    return true;

};
bool Screen::processEvents() {
    
    SDL_Event event;

    // Fetches latest event in queue of possible/awaiting events
    while (SDL_PollEvent(&event)) {

        // Check is user has quit
        if (event.type == SDL_QUIT) {
            return false;
        }
    }
    return true;
};

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
    
    // Check if pixel is within the screen boundary
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }

    Uint32 color = 0;

    color += red;
    color <<= 8;
    color += green;
    color <<= 8;
    color += blue;
    color <<= 8;
    color += 0xFF;

    // Format: RGBA

    m_buffer[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::update() {
    SDL_UpdateTexture(m_texture, NULL, m_buffer, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
    SDL_RenderPresent(m_renderer);
}

void Screen::boxBlur() {
    // Create a new screen of pixels, drawing second screen of pixels
    // Copy from one buffer and write to another
    // Swap pointers, buffer 2 to point to buffer 1

    // Swap the buffers using temp variable
    Uint32* temp = m_buffer;
    m_buffer = m_buffer2;
    m_buffer2 = temp;

    // Look at buffer 2 to give blur effect
        // Take screen, blur it, put onto screen
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            
            /* 0 0 0
               0 1 0 Pixel to become average of pixels around it
               0 0 0 Creates the box blur effect
            */

            int redTotal = 0;
            int greenTotal = 0;
            int blueTotal = 0;

            for (int row = -1; row <= 1; row++) {
                for (int col = -1; col <= 1; col++) {
                    int currentX = x + col;
                    int currentY = y + row;

                    // For each pixel, we end up iterating surrounding pixels
                    // Get colour values from these pixels and add then together
                        // Possible pixel is off edge of screen - create case where pixel is on screen
                    if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
                        Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];
                        Uint8 red = color >> 24;
                        Uint8 green = color >> 16;
                        Uint8 blue = color >> 8;

                        redTotal += red;
                        greenTotal += green;
                        blueTotal += blue;

                    }
                }
            }

            Uint8 red = redTotal / 9;
            Uint8 green = greenTotal / 9;
            Uint8 blue = blueTotal / 9;

            setPixel(x, y, red, green, blue);

        }
    }
}

void Screen::close() {
    // Freeing the memory of resources
    delete[] m_buffer;
    delete[] m_buffer2;
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyTexture(m_texture);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
};

}


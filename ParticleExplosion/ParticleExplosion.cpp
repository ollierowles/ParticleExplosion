#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
#include "Swarm.h"
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace sdl_components;

int main(int argc, char* argv[])
{

    srand(time(NULL)); // Will allow random number generator to change

    Screen screen;

    if (screen.init() == false) {
        cout << "Error initialising SDL." << endl;
    }

    Swarm swarm;


    // Traditional Game Loop 
    while (true) {
        // Updates particles

        // Draws particles

        // Returns milliseconds since the program started
        int elapsed = SDL_GetTicks();

        swarm.update(elapsed);

        unsigned char red = (unsigned char)((1 + sin(elapsed * 0.00101)) * 128); // Gives value is range of RGB limits 0-255
        unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128); // Gives value is range of RGB limits 0-255
        unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128); // Gives value is range of RGB limits 0-255

        const Particle * const pParticles = swarm.getParticles();
        for (int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i]; // Get particles 1-by-1
            int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH/2;
            int y = (particle.m_y) * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2;
            screen.setPixel(x, y, red, green, blue);
        }

        screen.boxBlur();

        // Draw the screen
        screen.update();


        // Check for messages/events
        if(screen.processEvents() == false) {
            break;
        }
    }

    screen.close();

    return 0;
}

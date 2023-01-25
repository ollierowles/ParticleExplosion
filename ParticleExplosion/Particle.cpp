#include "Particle.h"
#include <math.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

namespace sdl_components {

	Particle::Particle(): m_x(0), m_y(0) { // Initialises the particles to 0
		init();
	}

	void Particle::init() {
		m_x = 0;
		m_y = 0;
		m_direction = (2 * M_PI * rand()) / RAND_MAX; // Pick a random angle from 0-2pi
		m_speed = (0.02 * rand()) / RAND_MAX;

		m_speed *= m_speed; // Makes average distance between the particles to increases, exaggerates the distribution

	}

	Particle::~Particle() {


	}

	void Particle::update(int interval) {

		m_direction += interval * 0.0004;

		double xspeed = m_speed * cos(m_direction);
		double yspeed = m_speed * sin(m_direction);
		m_x += xspeed * interval; // Interval moves position relative to time passed since last update
		m_y += yspeed * interval; // Ensures that it will move similar speed on all computers
		
		if (m_x < -1 || m_x > 1 || m_y < -1 || m_y > 1) { // Checl if particle is out of bounds, if so assign a random value
			init(); // Reassign particles to centre, which are offscreen
		}

		// Take portion of particles on refresh and re-initialise randomly
		if (rand() < RAND_MAX / 100) { // 1 in every 100 times is true
			init();
		}


	};

}

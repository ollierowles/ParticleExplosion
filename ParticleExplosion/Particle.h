#pragma once
#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace sdl_components {

	// By default in a class, members are private. In struct they are public by default. 
	struct Particle {
		double m_x;
		double m_y;
	private:
		double m_speed; 
		double m_direction;

	private: 
		void init();

	public:
		Particle();
		virtual ~Particle();
		void update(int interval);
	};

};

#endif

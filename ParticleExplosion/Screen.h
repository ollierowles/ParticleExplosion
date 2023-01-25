#ifndef SCREEN_H_
#define SCREEN_H_

#include <iostream>
#include <SDL.h>


using namespace std;

namespace sdl_components {

class Screen
{
public: 
	// Constant Declaration
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;
private: 
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture; 
	Uint32* m_buffer;
	Uint32* m_buffer2;

public: 
	Screen();
	bool init();
	bool processEvents();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
	void update();
	void close();
	void boxBlur();
};

}

#endif /* SCREEN_H_ */

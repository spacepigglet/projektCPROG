#ifndef SYSTEM_H
#define SYSTEM_H

#include "Constants.h"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace tower {

	class System {
	public:
		System();
		~System();
		SDL_Renderer* get_ren() const;
		TTF_Font* get_font() const;
		
	private:
		SDL_Window* win;
		SDL_Renderer* ren;
		TTF_Font* font;
	};
	
	extern System sys; //says: there'a a definition of the system calles sys, but not here -> exists in cpp
	extern int WINDOW_HEIGHT;
	extern int WINDOW_WIDTH;
}

#endif
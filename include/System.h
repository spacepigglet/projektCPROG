#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace cwing {

	class System
	{
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
	
	extern System sys;
}

#endif
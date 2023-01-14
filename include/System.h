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
		std::string bg = "images/space-background-vector-21179778.jpg";
	};
	
	extern System sys; //säger: "det finns en definition av system som heter sys, men inte här!" finns i cpp
	extern int WINDOW_HEIGHT;
	extern int WINDOW_WIDTH;
}

#endif
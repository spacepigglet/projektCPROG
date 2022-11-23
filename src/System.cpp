#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <iostream>

namespace cwing {

	System::System()
	{
		std::cout << "*** System::System()\n";
		
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("Cwing", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 600, 400, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
		TTF_Init();
		font = TTF_OpenFont( (constants::gResPath + "fonts/arial.ttf").c_str(), 36);
		std::cout << "resPath: " << constants::gResPath << std::endl;
	}


	System::~System()
	{
		TTF_CloseFont(font);
		TTF_Quit();
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(ren);
		SDL_Quit();
	}

	SDL_Renderer* System::get_ren() const {
		return ren;
	}

	TTF_Font* System::get_font() const {
		return font;
	}
	
	System sys; // Statiskt globalt objekt (definierad utanför funktioner.)
}
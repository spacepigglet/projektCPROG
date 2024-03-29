#include "System.h"

namespace tower {

	System::System() {
		std::cout << "*** System::System()\n";
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("Tower game", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
		TTF_Init();
		font = TTF_OpenFont( (constants::gResPath_fonts + "arial.ttf").c_str(), 25);
		std::cout << "resPath: " << constants::gResPath_fonts << std::endl;
	}


	System::~System() {
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
	
	System sys; // global object (defined outside class)
	int WINDOW_WIDTH = 720;
	int WINDOW_HEIGHT = 720;
}
#include "System.h"

namespace tower {


	System::System()
	{
		std::cout << "*** System::System()\n";
		
		SDL_Init(SDL_INIT_EVERYTHING);
		win = SDL_CreateWindow("Tower game", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
		ren = SDL_CreateRenderer(win, -1, 0);
		TTF_Init();
		font = TTF_OpenFont( (constants::gResPath + "fonts/arial.ttf").c_str(), 36);
		std::cout << "resPath: " << constants::gResPath << std::endl;

		//Background* bg = new Background()
		//bg_tex = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + bg).c_str() );
	
	}


	System::~System()
	{
		//SDL_DestroyTexture(bg_tex);
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

	// SDL_Texture* System::get_bg_tex() const {
	// 	return bg_tex;
	// }
	
	System sys; // Statiskt globalt objekt (definierad utanför funktioner.)
	int WINDOW_WIDTH = 1080;
	int WINDOW_HEIGHT = 720;
}
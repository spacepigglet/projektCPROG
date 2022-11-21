#include <iostream>
#include <string>
#include "Constants.h" //gResPath-contains the path to your resources.

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_ttf.h>

// void jump(SDL_Rect& rect, SDL_Renderer& ren) {
// bool jumping = true;
// int orginalheight = rect.x;
// int height = rect.x + 50;
// while(jumping) {
//   if(rect.x < height) {
//     rect.x+=10;
//   }
//   SDL_RenderClear(renderer);
//     SDL_RenderCopy(renderer, bg_tex, NULL, NULL);
//     SDL_RenderCopy(renderer, spacepig_tex, NULL, &spacepig_rect);
//     SDL_RenderPresent(renderer);
// }
// jumping = false;

// }

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{
		std::cout << "Error SDL2 Initialization : " << SDL_GetError();
		return EXIT_FAILURE;
	}

	if (TTF_Init() < 0)
	{
		std::cout << "Error SDL_ttf Initialization : " << SDL_GetError();
		return EXIT_FAILURE;
	}
	
	SDL_Window* window 	= SDL_CreateWindow("Window", 100, 100, 800, 600, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//SDL_Surface* bg_sur = IMG_Load( (constants::gResPath + "images/bg.jpg").c_str() );
	SDL_Surface* bg_sur = IMG_Load( (constants::gResPath + "images/space-background-vector-21179778.jpg").c_str() );
	SDL_Surface* spacepig_sur = IMG_Load( (constants::gResPath + "images/spacepig3.png").c_str() );

  SDL_Rect spacepig_rect = {100, 100, (spacepig_sur->w)/2, (spacepig_sur->h)/2};
  Uint32 red = SDL_MapRGB(spacepig_sur->format, 255, 0, 0);
  SDL_SetColorKey(spacepig_sur, true, red);
 
	SDL_Texture* bg_tex = SDL_CreateTextureFromSurface(renderer, bg_sur);
	SDL_Texture* spacepig_tex = SDL_CreateTextureFromSurface(renderer, spacepig_sur);
	SDL_FreeSurface(bg_sur);
	SDL_FreeSurface(spacepig_sur);

	 std::cout << "End Program using the application\'s windows menu \"quit\" or just close the window!" << std::endl;

	// Loop till dess att programmet avslutas!
	bool running = true;
  //Sprite player{10, 10, "Amanda"};
	while (running) {
		SDL_Event event;
    while(SDL_PollEvent(&event)){
      switch (event.type) {
        case SDL_QUIT: running = false; break;
        case SDL_KEYDOWN: 
          switch(event.key.keysym.sym) {
            case SDLK_RIGHT: spacepig_rect.x+=10; break;
            case SDLK_LEFT: spacepig_rect.x-=10; break;
            case SDLK_UP:spacepig_rect.y-=10; break;
            case SDLK_DOWN:spacepig_rect.y+=10; break;
            // case SDLK_SPACE: jump(spacepig_rect, renderer);
          } break;
      if (event.key.keysym.sym == SDLK_END)
      running = true;
      break;
      } // switch
    }


    
		// if (SDL_PollEvent(&event)) {
		// 	if (event.type == SDL_QUIT) {
		// 		running = false;
		// 	}
		// }
    

		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bg_tex, NULL, NULL);
		SDL_RenderCopy(renderer, spacepig_tex, NULL, &spacepig_rect);
		SDL_RenderPresent(renderer);
	}

	// Städa innan programmet avslutas!

	SDL_DestroyTexture(bg_tex);
	SDL_DestroyTexture(spacepig_tex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
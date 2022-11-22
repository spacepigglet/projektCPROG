#include <iostream>
#include <string>
#include "Constants.h" //gResPath-contains the path to your resources.

#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h> 
#include <SDL2/SDL_mixer.h> 
#include <SDL2/SDL_ttf.h>
using namespace std;
#define FPS 65


void jump(SDL_Rect& rect, SDL_Renderer*& ren, SDL_Texture*& bg_tex, SDL_Texture*& figure_tex) {
int originalheight = rect.y;
int height = originalheight - 100;
const int tickInterval = 10000/FPS;
Uint32 nextTick = SDL_GetTicks() +  tickInterval;
while(rect.y > height) {
    rect.y-=10;
	SDL_RenderClear(ren);
    SDL_RenderCopy(ren, bg_tex, NULL, NULL);
    SDL_RenderCopy(ren, figure_tex, NULL, &rect);
    SDL_RenderPresent(ren);
	int delay = nextTick - SDL_GetTicks(); //får veta om det finns tid kvar innan nästa varv ska göras
		if (delay > 0)
			SDL_Delay(delay);
} 

while(rect.y < originalheight) {
    rect.y+=10;
	SDL_RenderClear(ren);
    SDL_RenderCopy(ren, bg_tex, NULL, NULL);
    SDL_RenderCopy(ren, figure_tex, NULL, &rect);
    SDL_RenderPresent(ren);
	int delay = nextTick - SDL_GetTicks(); //får veta om det finns tid kvar innan nästa varv ska göras
		if (delay > 0)
			SDL_Delay(delay);
}

}

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
	TTF_Font* font = TTF_OpenFont("c:/Windows/Fonts/arial.ttf", 36);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096); //frekvens(hälften av CD-frekv), 16 bitars  ljud, #kanaler(2=stereo), storlek på buffer
	Mix_Chunk* jump_soundEffect = Mix_LoadWAV("sounds/mixkit-quick-jump-arcade-game-239.wav");
	
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
	int varv = 0; //räkna varv för att kontollera hastigheten figuren rör sig i & blir samma på alla datorer
    const int tickInterval = 1000/FPS;

	Mix_PlayChannel(-1, jump_soundEffect, -1);
  //Sprite player{10, 10, "Amanda"};
	while (running) {
		//när nästa varv i loopen ska göras
		Uint32 nextTick = SDL_GetTicks() +  tickInterval; //GetTicks ger antal millisec sedan biblioteket startades
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
            case SDLK_SPACE: Mix_PlayChannel(-1, jump_soundEffect ,0);//vilken ljudkanal(-1=1st free channel), musik, antal upprepningar (-1 = loop)
					jump(spacepig_rect, renderer, bg_tex, spacepig_tex);
							
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
		varv++;    
		//skriv ut varv, ingen anledning, baa för att se hur man gör för att skriva ut löpande, 
		//Vi vill kanske kunna skriva ut höjd löpande senare
		string varvStr = to_string(varv);
		SDL_Color white = {255, 255, 255};
		SDL_Surface* varvSurf = TTF_RenderText_Solid(font, varvStr.c_str(), white);
		SDL_Texture* varvTx = SDL_CreateTextureFromSurface(renderer, varvSurf);
		//när vi ritar ut surface behöver vi rektangel
		SDL_Rect varvRect = {300, 300, varvSurf->w, varvSurf->h};
		SDL_FreeSurface(varvSurf); //släpper minnet som texture skapar i grafikkortet?


		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, bg_tex, NULL, NULL);
		SDL_RenderCopy(renderer, spacepig_tex, NULL, &spacepig_rect);
		SDL_RenderCopy(renderer, varvTx, NULL, &varvRect) ;//ska ritas ut på destination & str specificerad av varvRect
		SDL_RenderPresent(renderer);
		SDL_DestroyTexture(varvTx); //Blir ingen krah även när vi kör länge
		//Mix_FreeChunk(jump_soundEffect);

		int delay = nextTick - SDL_GetTicks(); //får veta om det finns tid kvar innan nästa varv ska göras
		if (delay > 0)
			SDL_Delay(delay);
	}

	// Städa innan programmet avslutas!

	SDL_DestroyTexture(bg_tex);
	SDL_DestroyTexture(spacepig_tex);
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_CloseFont(font);

	Mix_FreeChunk(jump_soundEffect);

	TTF_Quit();
	SDL_Quit();
	
	return EXIT_SUCCESS;
}
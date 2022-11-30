#include "Session.h"
#include <SDL2/SDL.h>
#include "System.h"

#include <iostream>
#define FPS 65
namespace tower {

	Session::Session() : quit(false){
		std::cout << "*** Session::Session()\n";

	}

	void Session::add(Component* c) {
		comps.push_back(c);
	}

	void Session::processInput(){
		SDL_Event eve;
			while (SDL_PollEvent(&eve)) {
				switch (eve.type) {
				case SDL_QUIT: quit = true; break;
				// case SDL_MOUSEBUTTONDOWN:
				// 	for (Component* c : comps)
				// 		c->mouseDown(eve);
				// 	break;
				// case SDL_MOUSEBUTTONUP:
				// 	for (Component* c : comps)
				// 		c->mouseUp(eve);
				// 	break;
				case SDL_KEYDOWN:
					for (Component* c : comps)
						c->keyDown(eve);
					break;
				case SDL_KEYUP:
					for (Component* c : comps)
						c->keyUp(eve);
					break;

				} // switch
			} // inre while
	}
	void Session::updateGame(){
		//hålla reda på tid
		//skicka update till actors
		//flytta plattformar
		//flytta bg
		//flytta enemies

	}

	void Session::generateOutput(){
		//SDL_SetRenderDrawColor(sys.get_ren(), 255, 255, 255, 255);
			SDL_RenderClear(sys.get_ren());
			SDL_RenderCopy(sys.get_ren(), sys.get_bg_tex(), NULL, NULL);
			for (Component* c : comps)
				c->draw();
			SDL_RenderPresent(sys.get_ren());
	}

	void Session::run() {
		
		while (!quit) {

			processInput();
			updateGame();
			generateOutput();

		
		} //yttre while

	}

	Session::~Session()
	{
	}
}
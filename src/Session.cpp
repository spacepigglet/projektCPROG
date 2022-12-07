#include "Session.h"
#include <SDL2/SDL.h>
#include "System.h"
#include "Component.h"
#include "Collision.h"

#include <iostream>
#define FPS 65
namespace tower {

	Session::Session() : quit(false){
		std::cout << "*** Session::Session()\n";

	}

	void Session::add(Component* c) {
		comps.push_back(c);
		if(Platform* p = dynamic_cast<Platform*>(c)){
            platforms.push_back(p);
		}
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
	
	void Session::updateGame() {
		for( Component* c: comps) {
			if(Actor *a = dynamic_cast <Actor*>(c)) {
				for( Platform* p : platforms) {
					if (Collision::collision(a, p)) {
						//std::cout << "COLLISION!" << std::endl;
						a->collisionWithPlatform(p);
					} 
			}
			}
			//c->update
		}
		//collisionDetection();
		
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
			for (Component* c : comps) {
				c->draw();
			}
			SDL_RenderPresent(sys.get_ren());
	}


	/*void Session::collisionDetection(){
		// for (unsigned int i = 0; i<comps.size(); i++) {
		// 	for(unsigned int j = 0; i<comps.size(); j++) {
		// 		if(Collision::collision(comps[i], comps[j])) {
		// 			std::cout << "Collision!" << std::endl;
		// 		}
		// 	}
		// }


		for (unsigned int i = 0; i<comps.size(); i++) {
			for(unsigned int j = 0; i<comps.size(); j++) {
				if(Collision::collision(comps[i]->getRect(), comps[j]->getRect())) {
					std::cout << "Collision!" << std::endl;
				}
			}
		}
        
    }*/

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

	Session ses;
}
#include "Session.h"
#include "Background.h"
#include <SDL2/SDL.h>
#include "System.h"
#include "Component.h"
#include "Collision.h"

#include <iostream>
#define FPS 65
namespace tower {

	Session::Session() : quit(false){
		std::cout << "*** Session::Session()\n";
		bg_Image = "images/space-background-vector-21179778.jpg";
	}

	void Session::add(Component* c) {
		comps.push_back(c);
		if(Platform* p = dynamic_cast<Platform*>(c)){
            platforms.push_back(p);
		}
	}

    void Session::set_background(std::string image) {
		bg_Image = image;
	}
	void Session::setup_background() {
		bg1 = Background::getInstance(0,0,WINDOW_WIDTH, WINDOW_HEIGHT, bg_Image);
		bg2 = Background::getInstance(-WINDOW_HEIGHT,0,WINDOW_WIDTH, WINDOW_HEIGHT, bg_Image);

		add(bg1); add(bg2);
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
			c->update();
			if(Actor *a = dynamic_cast <Actor*>(c)) {
				for( Platform* p : platforms) {
					if (Collision::collision(a, p)) {
						//std::cout << "COLLISION!" << std::endl;
						a->collisionWithPlatform(p);
					} 
			}
			}
			
		}
		
		//flytta ner allt mha c->moveY()

		//collisionDetection();
		
		//hålla reda på tid
		//skicka update till actors
		//flytta plattformar
		//flytta bg
		//flytta enemies

	}

	void Session::scroll() {
		for( Component* c: comps) {
			c->scroll(scrollSpeed);
		}
	}

	void Session::generateOutput(){
		//SDL_SetRenderDrawColor(sys.get_ren(), 255, 255, 255, 255);
			SDL_RenderClear(sys.get_ren());
			SDL_RenderCopy(sys.get_ren(), bg1->get_bg_tex(), NULL, NULL);
			SDL_RenderCopy(sys.get_ren(), bg2->get_bg_tex(), NULL, NULL);
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
		setup_background();
		const int tickInterval = 1000/FPS;
		while (!quit) {
			Uint32 nextTick = SDL_GetTicks() +  tickInterval; //GetTicks ger antal millisec sedan biblioteket startades
			int delay = nextTick - SDL_GetTicks(); //får veta om det finns tid kvar innan nästa varv ska göras
			processInput();
			updateGame();
			scroll();
			generateOutput();

			if (delay > 0)
				SDL_Delay(delay);
		
		} //yttre while

	}

	Session::~Session()
	{
		//SDL_DestroyTexture(bg_tex);
		delete bg1;
		delete bg2;
	}

	Session ses;
}
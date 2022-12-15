#include "Session.h"

#define FPS 60
namespace tower {

	Session::Session() : quit(false){
		std::cout << "*** Session::Session()\n";
		bg_Image = "images/space-background-vector-21179778.jpg";
		set_scroll_horizontal(false);
		//fptr= verticalScroll();
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
		bg2 = Background::getInstance(bg2_start_pos_x, bg2_start_pos_y, WINDOW_WIDTH, WINDOW_HEIGHT, bg_Image);

		//add(bg1); add(bg2);
	}

	void Session::set_scroll_horizontal(bool isHorizontal) {
      isScrolledHorizontally = isHorizontal;
	  if(isHorizontal){
		  bg2_start_pos_x = WINDOW_WIDTH;
		  bg2_start_pos_y = 0;
	  } else {
           bg2_start_pos_x = 0;
	       bg2_start_pos_y = -WINDOW_HEIGHT; 
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
		scroll();  //utkommenterat pga jobbigt haha
		
		//flytta ner allt mha c->moveY()

		//collisionDetection();
		
		//hålla reda på tid
		//skicka update till actors
		//flytta plattformar
		//flytta bg
		//flytta enemies

	}

	void Session::scroll() {
		// bg1->scrollFunc(scrollSpeed);
		// bg2->scrollFunc(scrollSpeed);
		// for( Component* c: comps) {
		// 	c->scrollFunc(scrollSpeed);
		// }

		if (isScrolledHorizontally){
			bg1->horizontalScroll(scrollSpeed);
		    bg2->horizontalScroll(scrollSpeed);
			for( Component* c: comps) {
				c->horizontalScroll(scrollSpeed);
			}
		}else {
			bg1->verticalScroll(scrollSpeed);
		    bg2->verticalScroll(scrollSpeed);
			for( Component* c: comps) {
				c->verticalScroll(scrollSpeed);
			}
		}
		
	}

	void Session::generateOutput(){
		//SDL_SetRenderDrawColor(sys.get_ren(), 255, 255, 255, 255);
			SDL_RenderClear(sys.get_ren());
			bg1->draw();
			bg2->draw();
			for (Component* c : comps) {
				c->draw();
			}
			
			SDL_RenderPresent(sys.get_ren());
	}

		void Session::initPlatforms(std::string image) {
			platform_image = image;
      for(int i = 0; i<10; i++) { 
				int platformGap = WINDOW_HEIGHT / 10;
				int y = 50 + (i * platformGap); //distance between platforms in y-led 
				//Måste se till s.a. window_height och antal plattformar man vill skapa går ihop med 
				//hur y beräknas, om man t.ex. sätter 100 som startvärde nu 
				// kommer bara 9 plattformar att synas i startläget.
				
        int x = rand() % (WINDOW_WIDTH - 100); //100 = längd på platform
        //int y = rand() % WINDOW_HEIGHT;

        Platform* p = Platform::getInstance(x, y, 100, 10, platform_image);
				add(p);
      }
		}

	void Session::run() {
		setup_background();
		const int tickInterval = 1000/FPS;
		while (!quit) {
			Uint32 nextTick = SDL_GetTicks() +  tickInterval; //GetTicks ger antal millisec sedan biblioteket startades
			int delay = nextTick - SDL_GetTicks(); //får veta om det finns tid kvar innan nästa varv ska göras
			processInput();
			updateGame();
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



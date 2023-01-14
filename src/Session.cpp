#include "Session.h"
#include "Enemy.h"
#include <memory> //for unique ptr

#define FPS 60
using namespace std;
namespace tower {

	Session::Session() : quit(false){
		std::cout << "*** Session::Session()\n";
		bg_Image = "images/space-background-vector-21179778.jpg";
		set_scroll_horizontal(false);
		setPlatformWidthRange(80, 200);
		//fptr= verticalScroll();
	}

	void Session::add(Component* c) {
		comps.push_back(c);
		if(MobileComponent* m = dynamic_cast<MobileComponent*>(c)){ //bra lösning? platformar är rörliga och de är många...
      mobileComps.push_back(m);
		}
		if(Enemy* e = dynamic_cast<Enemy*>(c)){
       enemies.push_back(e);
		}
		if(Platform* p = dynamic_cast<Platform*>(c)){
      platforms.push_back(p);
		}
		if(Actor* a = dynamic_cast<Actor*>(c)){
      player = a;
		}
		
	}

	void Session::remove(Component* c) { //anropas t.ex. i Enemy.cp
		removedComps.push_back(c);
		if(MobileComponent* mc = dynamic_cast<MobileComponent*>(c)) {
			removedMobileComps.push_back(mc);
		}
		if(Platform* p = dynamic_cast<Platform*>(c)) {
			removedPlatforms.push_back(p);
		}
		if(Enemy* e = dynamic_cast<Enemy*>(c)) {
			removedEnemies.push_back(e);
		}
	}

    void Session::set_background(std::string image) {
		bg_Image = image;
	}

	void Session::setPlatformImage(std::string image){
		platform_image = image;
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
			case SDL_MOUSEBUTTONDOWN:
				for (Component* c : comps)
					c->mouseDown(eve);
				break;
			case SDL_MOUSEBUTTONUP:
				for (Component* c : comps)
					c->mouseUp(eve);
				break;
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
		//This code is before the update() bc update will move the platform to the top so in that case this code will never run:
		for( Component* c: comps) {
			if(Platform* p = dynamic_cast<Platform*>(c)) {
				if(((p->getUpperY() > WINDOW_HEIGHT + p->getHeight()) || ((p->getRightX() < 0))) && p->shouldBeRemoved()) {
						remove(p);
				}
			}
			c->update();
		}
		//player is allowed 50 points outside window. More than that-> game over
		if ((isScrolledHorizontally && ( (player->getRightX() < -50) || (player->getUpperY() > WINDOW_HEIGHT + 50))) || ( 
			(!isScrolledHorizontally &&(player->getUpperY() > WINDOW_HEIGHT + 50)))){
				quit = true;
		}

		for(unsigned int i = 0; i<mobileComps.size()-1; i++) {
			MobileComponent* current = mobileComps[i];
			for(unsigned int j = i+1; j<mobileComps.size(); j++) {
				MobileComponent* next = mobileComps[j];
				if(Collision::collision(current, next)) {
					current->handleCollision(next); //generalisera i mobilecomponent
					next->handleCollision(current);
				}
			}
		}
		
		if (player->isDead()){
			quit = true;
		}
			
		for(Enemy* e : enemies) {
			if(!(e->isAlive())) {
				remove(e);
			}
		}
		removeComponents();
		addEnemy();

		scroll();  //utkommenterat pga jobbigt haha
		
	}

	void Session::addEnemy() {
		for(unsigned int i = 0; i<(platforms.size()-2); i+=2) {
			if(platforms[i]->getUpperY() == 0) {
				add(Enemy::getInstance(platforms[i]->getLeftX(), platforms[i]->getUpperY() - 50, 50, 50, enemy_image, platforms[i]));
			} else if(platforms[i]->getLeftX() == WINDOW_WIDTH) { //horizontal scroll
				add(Enemy::getInstance(platforms[i]->getLeftX(), platforms[i]->getUpperY() - 50, 50, 50, enemy_image, platforms[i]));
			}
		}
	}


	void Session::removeComponents() {

		for(Platform* p: removedPlatforms) {
			for(std::vector<Platform*>::iterator it=platforms.begin(); it != platforms.end();) {
				if(*it == p) {
						it = platforms.erase(it);
				} else {
					it++;
				}
			}
	}
	removedPlatforms.clear();

	for(MobileComponent* mc: removedMobileComps) {
			for(std::vector<MobileComponent*>::iterator it=mobileComps.begin(); it != mobileComps.end();) {
				if(*it == mc) {
						it = mobileComps.erase(it);
				} else {
					it++;
				}
			}
	}
	removedMobileComps.clear();

	for(Enemy* e: removedEnemies) {
			for(std::vector<Enemy*>::iterator it=enemies.begin(); it != enemies.end();) {
				if(*it == e) {
						it = enemies.erase(it); 
				} else {
					it++;
				}
			}
	}
	removedEnemies.clear();

	for(Component* c: removedComps) {
				for(std::vector<Component*>::iterator it=comps.begin(); it != comps.end();) {
					if(*it == c) {
						delete *it;
							it = comps.erase(it); 
					} else {
						it++;
					}
				}
		}
		removedComps.clear();

}
	

	void Session::scroll() {
		if (isScrolledHorizontally){
			bg1->horizontalScroll(scrollSpeed);
		    bg2->horizontalScroll(scrollSpeed);
			for( MobileComponent* m: mobileComps) {
				m->horizontalScroll(scrollSpeed);
			}
		}else {
			bg1->verticalScroll(scrollSpeed);
		    bg2->verticalScroll(scrollSpeed);
			for( MobileComponent* m: mobileComps) {
				m->verticalScroll(scrollSpeed);
			}
		}
		
	}

	 void Session::setPlatformWidthRange(int min, int max) {
	 	platformMinWidth = min;
		platformMaxWidth = max;
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
		for(int i = 0; i<nrOfPlatforms; i++) { 
			int platformGapY = WINDOW_HEIGHT / nrOfPlatforms; 
			int y = 20 + (i * platformGapY); //distance between platforms in y-led 
			
			int width = (rand() % (platformMaxWidth- platformMinWidth + 1)) + platformMinWidth; //random nr between min and max platform width
			int x = rand() % (WINDOW_WIDTH - width); //random nr within window
			add(Platform::getInstance(x, y, width, platformHeight, platform_image));
		}
	}

	void Session::initEnemies(std::string image) {
		enemy_image = image;
		for(unsigned int i = 0; i<(platforms.size()-2); i+=2) {
			add(Enemy::getInstance(platforms[i]->getLeftX(), platforms[i]->getUpperY() - 50, 50, 50, enemy_image, platforms[i]));
		}
	}
//Session ses;
	class RestartButton: public Button {
		public:
		RestartButton(Session* ses) :Button(WINDOW_WIDTH/4, WINDOW_HEIGHT/2, 200, 100, "Restart"), session(ses) {}
		void perform(Button* source) override{
			session->isQuitting(false);
			session->reset();
			session->run();
		}
		private:
		Session* session;
	};

	class QuitButton: public Button {
		public:
		QuitButton(Session* ses) :Button(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 200, 100, "Quit"), session(ses)  {}
		void perform(Button* source) override{
			session->isQuitting(false);
		}
		private:
		Session* session;
	};

	void Session::gameOver(){
		
		RestartButton* restartButton = new RestartButton(this);
		QuitButton* quitButton = new QuitButton(this);
		add(restartButton);
		add(quitButton);
		
	}

	void Session::reset(){
		//reset/clean up
		comps.clear(); //deletes pointers in vector, not objects
		mobileComps.clear();
		for (Platform* p : platforms) {
			remove(p);
		}
		platforms.clear();
		for(Enemy* e: enemies) {
			remove(e);
		}
		enemies.clear();
		removeComponents();

		//restart
		initPlatforms(platform_image);
		initEnemies(enemy_image);
		player->reset();
		add(player);
	}

//main gameloop
	void Session::run() {
		setup_background();

		const int tickInterval = 1000/FPS;
		Uint32 nextTick;
		int delay;
		while (!quit) {
			nextTick = SDL_GetTicks() +  tickInterval; //GetTicks ger antal millisec sedan biblioteket startades
			delay = nextTick - SDL_GetTicks(); //får veta om det finns tid kvar innan nästa varv ska göras
			processInput();
			updateGame();
			generateOutput();

			if (delay > 0)
				SDL_Delay(delay);
		
		} //yttre while


		gameOver();
		while (quit){
			nextTick = SDL_GetTicks() +  tickInterval; //GetTicks ger antal millisec sedan biblioteket startades
			delay = nextTick - SDL_GetTicks(); //får veta om det finns tid kvar innan nästa varv ska göras
			processInput();
			generateOutput();

			if (delay > 0)
				SDL_Delay(delay);
		}
	}

	Session::~Session()
	{
		//SDL_DestroyTexture(bg_tex);
		delete bg1;
		delete bg2;
	}

	Session ses;

}

	






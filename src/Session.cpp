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

	void Session::addTemp(Component* c) {
		tempComps.push_back(c);
		
		if(MobileComponent* m = dynamic_cast<MobileComponent*>(c)){ 
            tempMobileComps.push_back(m);
		}}

	void Session::remove(Component* c) { //anropas t.ex. i Enemy.cpp
		removedComps.push_back(c);
		//std::cout << "Enemy is in removedComps" << std::endl; -> FUNKAR
	}
		
	

	void Session::addCompsFromTemp(){
		for(Component* c : tempComps){
			comps.push_back(c);

		}
		for (MobileComponent* mc : tempMobileComps){
			mobileComps.push_back(mc);
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
		for( Component* c: comps) {
			c->update();
		}
		//player is allowed 50 points outside window. More than that-> game over
		if ((isScrolledHorizontally && (player->getRightX() < -50)) || ( 
			(!isScrolledHorizontally &&(player->getUpperY() > WINDOW_HEIGHT + 50)))){
				quit = true;
		}

		for(unsigned int i = 0; i<mobileComps.size()-1; i++) {
				MobileComponent* current = mobileComps[i];
				for(unsigned int j = i+1; j<mobileComps.size(); j++) {
					MobileComponent* next = mobileComps[j];
					if(Collision::collision(current, next)) {
						//std::cout << "Collision with:" << i << " and " << j << std::endl;
						current->handleCollision(next); //generalisera i mobilecomponent
						next->handleCollision(current);
						//std::cout << "Collision handled" << std::endl;
					}
				}
		}
		for(Enemy* e : enemies) {
			if(!(e->isAlive())) {
				removeEnemy(e);
			}
		}
		addEnemy();
		number_of_lives->setText(to_string(player->getHealth()));
		
		scroll();  //utkommenterat pga jobbigt haha
		
		//flytta ner allt mha c->moveY()

		//collisionDetection();
		
		//hålla reda på tid
		//skicka update till actors
		//flytta plattformar
		//flytta bg
		//flytta enemies
	}

	void Session::addEnemy() {
		for(unsigned int i = 0; i<(platforms.size()-2); i+=2) {
			if(platforms[i]->getUpperY() == 0) {
				add(Enemy::getInstance(platforms[i]->getLeftX(), platforms[i]->getUpperY() - 50, 50, 50, enemy_image, platforms[i]));
			} 
		}
	}

	void Session::removeEnemy(Enemy* e) {
		
   std::unique_ptr<Enemy> enemyPtr(e); //ska ta hand om pekarna?

		for(std::vector<Component*>::iterator it=comps.begin();
		it != comps.end();) {
		if(*it == e) {
		it = comps.erase(it, it+1);
		std::cout << "enemy deleted from comps" << std::endl;
		std::cout << comps.size() << std::endl;
		} else {
		++it;
		}
		}

		for(std::vector<MobileComponent*>::iterator it2=mobileComps.begin();
		it2 != mobileComps.end();) {
		if(*it2 == e) {
		it2 = mobileComps.erase(it2, it2+1);
		std::cout << "enemy deleted from mobilecomps" << std::endl;
		std::cout << mobileComps.size() << std::endl;
		} else {
		++it2;
		}
		}

		for(std::vector<Enemy*>::iterator it3=enemies.begin();
		it3 != enemies.end();) {
		if(*it3 == e) {
		it3 = enemies.erase(it3, it3+1);
		std::cout << "enemy deleted from enemies" << std::endl;
		std::cout << enemies.size() << std::endl;
		} else {
		++it3;
		}
		}
     
}
	

	void Session::scroll() {
		// bg1->scrollFunc(scrollSpeed);
		// bg2->scrollFunc(scrollSpeed);
		// for( Component* c: mobileComps) {
		// 	c->scrollFunc(scrollSpeed);
		// }

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
			// string livesStr = to_string(player->getHealth());
			// SDL_Color white = {255,255,255};
			// SDL_Surface* lives_Surf = TTF_RenderText_Solid(sys.get_font(), livesStr.c_str(), white);
			// SDL_Texture* livesTx = SDL_CreateTextureFromSurface(sys.get_ren(), lives_Surf);
			// SDL_Rect lives_rect = {WINDOW_WIDTH-20, 10, lives_Surf->w, lives_Surf->h};
			// SDL_RenderCopy(sys.get_ren(), livesTx, NULL, &lives_rect);
			
			
			SDL_RenderPresent(sys.get_ren());
	}

	void Session::initPlatforms(std::string image) {
	    platform_image = image;
		for(int i = 0; i<nrOfPlatforms; i++) { 
			int platformGapY = WINDOW_HEIGHT / nrOfPlatforms; //player->getHeight()
			int y = 20 + (i * platformGapY); //distance between platforms in y-led 
			
			int width = (rand() % (platformMaxWidth- platformMinWidth + 1)) + platformMinWidth; //random nr between min and max platform width
			int x = rand() % (WINDOW_WIDTH - width); //random nr within window
			//int y = rand() % WINDOW_HEIGHT;
			add(Platform::getInstance(x, y, width, platformHeight, platform_image));
		}
	}

	void Session::initEnemies(std::string image) {
			enemy_image = image;
			for(Platform* p : platforms) {
				add(Enemy::getInstance(p->getLeftX(), p->getUpperY() - 50, 50, 50, enemy_image, p));
			}
	}
//Session ses;
	class RestartButton: public Button {
		public:
		RestartButton(Session* ses) :Button(WINDOW_WIDTH/4, WINDOW_HEIGHT/2, 200, 100, "Restart"), session(ses) {}
		void perform(Button* source) override{
			session->quit = false;
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
			session->quit = false;
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
			delete p;
		}
		platforms.clear();
		for(Enemy* e: enemies) {
			delete e;
		}
		
		platformChunk1.clear();
		platformChunk2.clear();

		//restart
		initPlatforms(platform_image);
		initEnemies(enemy_image);
		player->reset();
		comps.push_back(player);

		
	}

//skapar en ny, stor platform och ser till att den skapas och när den är utanför så försvinner den
//sätter (implementation) att man börjar på den höjden -- 

//main gameloop

void Session::setup_lives(){
	number_of_lives = Label::getInstance(WINDOW_WIDTH-20, 10, 20, 20, to_string(player->getHealth()), {255,255,255});
	add(number_of_lives);

}
	void Session::run() {
		setup_background();
		setup_lives();
		//initPlatforms();
		
		/*setup_start_platform();
		if(!horisontalscroll) {
			new Platform();
		}*/
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

	






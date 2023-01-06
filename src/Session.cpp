#include "Session.h"
#include "Enemy.h"

#define FPS 60
namespace tower {

	Session::Session() : quit(false){
		std::cout << "*** Session::Session()\n";
		bg_Image = "images/space-background-vector-21179778.jpg";
		set_scroll_horizontal(false);
		setPlatformWidthRange(80, 200);
		//fptr= verticalScroll();
	}

	
  
    // Copy constructor
    Session::Session(Session& s)
    {
        bg_Image = s.bg_Image;
		platform_image = s.platform_image;
		enemy_image = s.enemy_image;
        scrollSpeed = s.scrollSpeed;
		isScrolledHorizontally = s.isScrolledHorizontally;
		platformMaxWidth = s.platformMaxWidth;
		platformMinWidth = s.platformMinWidth;
		player = s.player;

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
			//if(Actor *a = dynamic_cast <Actor*>(c)) { //fundera på om det finns ett bättre sätt!
				for( Enemy* e : enemies) {
					if (Collision::collision(player, e)) {
						//std::cout << "COLLISION!" << std::endl;
						player->collisionWithEnemy(e);
						if(!(e->isEnemyAlive())) {
							remove(e);
						}
					} 
				}
				for( Platform* p : platforms) {
					if (Collision::collision(player, p)) {
						//std::cout << "COLLISION!" << std::endl;
						player->collisionWithPlatform(p);
					} 
					}
				//player is allowed 50 points outside window. More than that-> game over
				if ((isScrolledHorizontally && (player->getRightX() < -50)) || (
				   (!isScrolledHorizontally &&(player->getUpperY() > WINDOW_HEIGHT + 50)))){
						quit = true;
					}
				} 
			//}
		

		//FUNKAR EJ!!!! !!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//Testat lägga den på flera olika ställen i denna loop osv men den körs inte.
		//Ska ta bort element från Sessionen -> 
		//först anropas metoden remove() (i t.ex. Enemy när den dör) 
		//och Enemy-objektet läggs till i vektorn removedComps som sedan ska itereras igenom och ta bort Enemy:
		for(Component* c: removedComps) {
			//std::cout << "Remove loopen körs" << std::endl;
			for(std::vector<Component*>::iterator it=comps.begin();
			it != comps.end();) {
				if(*it == c) {
						it = comps.erase(it); //plockar ut från vektorn
						//std::cout << "Enemy deleted" << std::endl;
				} else {
					it++;
				}
				removedComps.clear();
			}
		}

		//DENNA KÖRS ALDRIG...
		
		//scroll();  //utkommenterat pga jobbigt haha
		
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
			
			SDL_RenderPresent(sys.get_ren());
	}

	void Session::initPlatforms(std::string image) {
	    platform_image = image;
		for(int i = 0; i<nrOfPlatforms; i++) { 
			int platformGapY = WINDOW_HEIGHT / nrOfPlatforms; //player->getHeight()
			int y = 20 + (i * platformGapY); //distance between platforms in y-led 
			//Måste se till s.a. window_height och antal plattformar man vill skapa går ihop med 
			//hur y beräknas, om man t.ex. sätter 100 som startvärde nu 
			// kommer bara 9 plattformar att synas i startläget.
			
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
			session->askingForRestart = false;
			session->restart = true;
			//session->reset();
			//session->run();
		}
		private:
		Session* session;
	};

	class QuitButton: public Button {
		public:
		QuitButton(Session* ses) :Button(WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 200, 100, "Quit"), session(ses)  {}
		void perform(Button* source) override{
			session->askingForRestart = false;
		}
		private:
		Session* session;
	};

	void Session::gameOver(){
		askingForRestart = true;
		RestartButton* restartButton = new RestartButton(this);
		QuitButton* quitButton = new QuitButton(this);
		add(restartButton);
		add(quitButton);
		
	}

	void Session::reset(){

		comps.clear();
		mobileComps.clear();
		for (Platform* p : platforms) { //How does this work? You can't delete during this kind of iteration...?
			delete p;
		}
		platforms.clear();
		for(Enemy* e: enemies) {
			delete e;
		}
		enemies.clear(); //pointers removed from vectors.
		platformChunk1.clear();
		platformChunk2.clear();
		initPlatforms(platform_image);
		initEnemies(enemy_image);
		player->reset();
		comps.push_back(player);

		
	}

//skapar en ny, stor platform och ser till att den skapas och när den är utanför så försvinner den
//sätter (implementation) att man börjar på den höjden -- 

//main gameloop
	bool Session::run() {
		setup_background();
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

		return restart;
	}

	Session::~Session()
	{
		//SDL_DestroyTexture(bg_tex);
		delete bg1;
		delete bg2;
	}

	Session ses;

}

	






#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"
#include "Background.h"
#include "Platform.h"
#include <SDL2/SDL.h>
#include "System.h"
#include "Collision.h"
#include <iostream>
#include "Actor.h"
//#include "MobileComponent.h"
#include <cstdlib>
#include "Button.h"
#include "Label.h"

#include "Enemy.h"

namespace tower {

	class Session
	{
	public:
		Session();
		void add(Component* c);
		void remove(Component* c);
		void set_background(std::string);
		void run();
		~Session();
		//const std::vector<MobileComponent*> getComps() const {return mobileComps;}
		void setPlatformWidthRange(int, int); 
		void initPlatforms(std::string);
		void initEnemies(std::string);
		void processInput();
		void updateGame();
		void generateOutput();
		void scroll();
		void set_scroll_horizontal(bool isHorizontal);
		void reset();
		void setPlatformImage(std::string);
		void addEnemy();
		void isQuitting(bool q) {quit = q;}

		//bool quit;

	private:
		bool quit;
		void gameOver();
	  void setup_background();
		void setup_lives();
		void removeComponents();
		std::vector<Component*> tempComps;
		//std::vector<MobileComponent*> tempMobileComps;
		
		std::vector<Component*> comps;
		std::vector<Component*> removedComps;
		//std::vector<MobileComponent*> removedMobileComps;
		std::vector<Enemy*> removedEnemies;
		std::vector<Platform*> removedPlatforms;
		//std::vector<MobileComponent*> mobileComps;
		std::vector<Platform*> platforms;
		std::vector<Platform*> platformChunk1;
		std::vector<Platform*> platformChunk2;
		std::vector<Enemy*> enemies;
		//void collisionDetection();
		
		int scrollSpeed = 1;
		Background* bg1 ;
		Background* bg2 ;
		std::string bg_Image;
		std::string platform_image;
		std::string enemy_image;
		bool isScrolledHorizontally;
		int bg2_start_pos_x;
		int bg2_start_pos_y;
		int nrOfPlatforms = 10;
		int platformMinWidth;
		int platformMaxWidth;
		int platformHeight = 10;
		Actor* player;
		Label* number_of_lives;
		Platform* startPlatform;
		
		//void (*fpek)() ;
		//typedef void (*func_t)(int); // pointer to function with no args and void return
        //func_t fptr; // variable of pointer to function

	};

	extern Session ses;
}
#endif
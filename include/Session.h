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
#include "MobileComponent.h"
#include <cstdlib>
#include "Enemy.h"

namespace tower {

	class Session
	{
	public:
		Session();
		void add(Component* c);
		void remove(Component* c);
		//void add(Background* b);
		void set_background(std::string);
		void run();
		~Session();
		const std::vector<MobileComponent*> getComps() const {return mobileComps;}
		void setPlatformWidthRange(int, int); 
		void initPlatforms(std::string);
		void initEnemies(std::string);
		void processInput();
		void updateGame();
		void generateOutput();
		void scroll();
		void set_scroll_horizontal(bool isHorizontal);
        
		// SDL_Texture* get_bg_tex1() const {return bg1->get_bg_tex();}
		// SDL_Texture* get_bg_tex2() const {return bg2->get_bg_tex();}

	private:
	  void setup_background();
		std::vector<Component*> comps;
		std::vector<Component*> removedComps;
		std::vector<MobileComponent*> mobileComps;
		std::vector<Platform*> platforms;
		std::vector<Enemy*> enemies;
		//void collisionDetection();
		bool quit;
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
		/*int platformMinWidth;
		int platformMaxWidth;
		int platformHeight = 10;*/
		Actor* player;
		
		//void (*fpek)() ;
		//typedef void (*func_t)(int); // pointer to function with no args and void return
        //func_t fptr; // variable of pointer to function

	};

	extern Session ses;
}
#endif
#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include <SDL2/SDL.h>
#include <iostream>

#include "System.h"
#include "Component.h"
#include "Background.h"
#include "Platform.h"
#include "Collision.h"
#include "Actor.h"
#include "Label.h"
#include "Button.h"
#include "Enemy.h"

namespace tower {

	class Session {
	public:
		Session();
		~Session();
		void add(Component* c);
		void set_background(const std::string);
		void run();
		void setPlatformWidthRange(int, int); 
		const void initPlatforms(const std::string);
		const void initEnemies(const std::string);
		void set_scroll_horizontal(bool isHorizontal);
		void setPlatformImage(std::string);
		void isQuitting(bool q) {quit = q;}
		void reset();

	private:
		void gameOver();
	  void setup_background();
		void removeComponents();
		const void processInput();
		const void updateGame();
		const void generateOutput();
		void scroll();
		void addToRemove(Component* c);
		void addEnemy();

		bool quit;
		int scrollSpeed = 1;
		bool isScrolledHorizontally;
		int bg2_start_pos_x;
		int bg2_start_pos_y;
		const int nrOfPlatforms = 12;
		int platformMinWidth;
		int platformMaxWidth;
		const int platformHeight = 10;
		Actor* player;

		std::vector<Component*> comps;
		std::vector<Component*> compsToRemove;
		std::vector<Enemy*> enemiesToRemove;
		std::vector<Platform*> platformsToRemove;
		std::vector<Platform*> platforms;
		std::vector<Enemy*> enemies;
	
		Background* bg1;
		Background* bg2;

		std::string bg_Image;
		std::string platform_image;
		std::string enemy_image;
	
	};

	
}
#endif
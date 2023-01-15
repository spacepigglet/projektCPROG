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
#include "Label.h"
#include <cstdlib>
#include "Button.h"
#include "Label.h"
#include "ImmobileComponent.h"


#include "Enemy.h"

namespace tower {
	class RestartButton;
	class QuitButton;

	class Session {
	public:
		Session();
		void add(Component* c);
		void addToRemove(Component* c);
		void set_background(const std::string);
		void run();
		~Session();
		void setPlatformWidthRange(int, int); 
		const void initPlatforms(const std::string);
		const void initEnemies(const std::string);
		const void processInput();
		const void updateGame();
		const void generateOutput();
		void scroll();
		void set_scroll_horizontal(bool isHorizontal);
		void reset();
		void setPlatformImage(std::string);
		void addEnemy();
		void isQuitting(bool q) {quit = q;}

	private:
		bool quit;
		void gameOver();
	  void setup_background();
		void removeComponents();
		std::vector<Component*> tempComps;
		std::vector<Component*> comps;
		std::vector<Component*> removedComps;
		std::vector<Enemy*> removedEnemies;
		std::vector<Platform*> removedPlatforms;
		std::vector<Platform*> platforms;
		std::vector<Platform*> platformChunk1;
		std::vector<Platform*> platformChunk2;
		std::vector<Enemy*> enemies;
		
		const int scrollSpeed = 1;
		Background* bg1 ;
		Background* bg2 ;
		std::string bg_Image;
		std::string platform_image;
		std::string enemy_image;
		bool isScrolledHorizontally;
		int bg2_start_pos_x;
		int bg2_start_pos_y;
		const int nrOfPlatforms = 10;
		int platformMinWidth;
		int platformMaxWidth;
		const int platformHeight = 10;
		Actor* player;
		Label* number_of_lives;
		Platform* startPlatform;
		RestartButton* restartButton;
		QuitButton* quitButton;
		
	};


	class RestartButton: public Button {
	public:
	RestartButton(Session* ses);
	void perform(Button* source) override;
	~RestartButton();
	private:
	Session* session;
	};



class QuitButton: public Button {
	public:
	QuitButton(Session* ses);
	void perform(Button* source) override;
	~QuitButton();
	private:
	Session* session;
	};

	extern Session ses;
}
#endif
#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"
#include "Background.h"
#include "Platform.h"
#include <SDL2/SDL.h>

namespace tower {

	class Session
	{
	public:
		Session();
		void add(Component* c);
		//void add(Background* b);
		void set_background(std::string);
		void run();
		~Session();
		const std::vector<Component*> getComps() const {return comps;}
		void processInput();
		void updateGame();
		void generateOutput();
		void scroll();
		// SDL_Texture* get_bg_tex1() const {return bg1->get_bg_tex();}
		// SDL_Texture* get_bg_tex2() const {return bg2->get_bg_tex();}

	private:
		std::vector<Component*> comps;
		std::vector<Platform*> platforms;
		void collisionDetection();
		bool quit;
		int scrollSpeed = 1;
		Background* bg1 ;
		Background* bg2 ;
	};

	//extern Session ses;
}
#endif
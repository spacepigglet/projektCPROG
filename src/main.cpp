

#include <SDL2/SDL.h>

#include "Session.h"
#include "Button.h"
#include "Actor.h"
#include "Platform.h"
#include <string>
#include "Background.h"

#include <iostream>

/*
*   'gResPath' is a global constant defined in "Constants.h", 
*   representing the relative path to your resource folders as a string,
*   i.e. ' const std::string gResPath = "../../resources/" '
*   Use it through its namespace, 'constants::gResPath'.
*/

using namespace std;
using namespace tower;

class HealthLabel : public Label {
	public:
	HealthLabel(int x, int y, int w, int h, std::string txt, SDL_Color color, Actor* a);
	void update();

	private:
	Actor* player;
};

HealthLabel::HealthLabel(int x, int y, int w, int h, std::string txt, SDL_Color color, Actor* a):
	Label(x,y,w,h,txt,color), player(a){

	}
void HealthLabel::update(){
	setText(to_string(player->getHealth()));
}




int main(int argc, char** argv) {
	std::cout << "*** main()\n";

	Session ses;
	Actor* a = Actor::getInstance(150, 0, 70, 100, "images/spacepig_transparent.png", 3);
	//ses.set_scroll_horizontal(true);
	
	HealthLabel* health_lbl = new HealthLabel(WINDOW_WIDTH-20, 10, 20, 20, to_string(a->getHealth()), {255,255,255}, a);
	ses.add(health_lbl);
	
	ses.set_background("images/space-background-vector-21179778.jpg");

	//ses.setPlatformImage("images/marble.jpg");

	//ses.add(a); //temp bcz needs to be added after platforms for rendering
	Platform* start = Platform::getInstance(WINDOW_WIDTH/2 - 250, 500, 500, 10, "images/marble.jpg", true);
	ses.add(start);
	ses.initPlatforms("images/marble.jpg");
	ses.initEnemies("images/enemy-orange.png");
	ses.add(a);
	

	ses.run();
	
	return 0;
}
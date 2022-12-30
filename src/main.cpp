

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




int main(int argc, char** argv) {
	std::cout << "*** main()\n";

	Session ses;
	Actor* a = Actor::getInstance(150, 0, 70, 100, "images/spacepig_transparent.png");
	//ses.set_scroll_horizontal(true);

	
	ses.set_background("images/space-background-vector-21179778.jpg");

	//ses.setPlatformImage("images/marble.jpg");

	//ses.add(a); //temp bcz needs to be added after platforms for rendering
	

	ses.initPlatforms("images/marble.jpg");
	ses.initEnemies("images/enemy-orange.png");
	ses.add(a);
	

	ses.run();
	
	return 0;
}
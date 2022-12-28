

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
	//Background* b = Background::getInstance(0, 0, 1080, 780, "images/space-background-vector-21179778.jpg");
	Actor* a = Actor::getInstance(150, 0, 70, 100, "images/spacepig_transparent.png");
	/*Platform* p = Platform::getInstance(100, 200, 100, 10, "images/marble.jpg");
	Platform* p2 = Platform::getInstance(300, 400, 100, 10, "images/marble.jpg");
	Platform* p3 = Platform::getInstance(250, 300, 100, 10, "images/marble.jpg");
	Platform* p4 = Platform::getInstance(-500, 500, 2000, 10, "images/marble.jpg");*/
	
	ses.set_scroll_horizontal(true);

	//ses.add(b);
	ses.set_background("images/space-background-vector-21179778.jpg");
	ses.initPlatforms("images/marble.jpg");
	ses.initEnemies("images/enemy-orange.png");
	ses.add(a);
	//ses.add(p);
	/*ses.add(p2);
	ses.add(p3);
	ses.add(p4);*/
	ses.run();
	
	return 0;
}
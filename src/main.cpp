

#include <SDL2/SDL.h>

#include "Session.h"
#include "Button.h"
#include "Actor.h"
#include "Platform.h"
#include <string>

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
	Actor* a = Actor::getInstance(100, 100, 70, 100, "images/spacepig_transparent.png");
	Platform* p = Platform::getInstance(100, 200, 100, 10, "images/marble.jpg");

	
	ses.add(a);
	ses.add(p);
	ses.run();
	
	return 0;
}
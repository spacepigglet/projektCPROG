#include "Component.h"

namespace tower {

	Component::Component(int x, int y, int w, int h) :rect{ x,y,w,h } {

	}
	
	Component::Component(int x, int y, int w, int h, bool scrollable) :
		rect{ x,y,w,h }, isScrollable(scrollable) {
		
	}

	Component::~Component()
	{
	}


	void Component::horizontalScroll(int toScroll) {
		moveX(-toScroll);
	}

	void Component::verticalScroll(int toScroll) {
		moveY(toScroll);
	}

	void Component::scroll(bool horizontal, int toScroll){
		if(isScrollable){
			if (horizontal)
				horizontalScroll(toScroll);
			else
				verticalScroll(toScroll);
		}
		
	}

  void Component::setPosition(int x, int y) {
		rect.x = x;
		rect.y = y;
	}

	/* void Component:: draw() const {
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &rect);
    } */

}
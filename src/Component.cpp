#include "Component.h"

namespace tower {

	Component::Component(int x, int y, int w, int h) :rect{ x,y,w,h } //int leftX, int upperY, int rightX , int lowerY
	{
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

	void Component::setPosition(int x, int y) {
		rect.x = x;
		rect.y = y;
	}
}
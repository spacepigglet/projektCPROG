#include "Component.h"

namespace tower {

	Component::Component(int x, int y, int w, int h) :rect{ x,y,w,h } //int leftX, int upperY, int rightX , int lowerY
	{
	}


	Component::~Component()
	{
	}

	void Component::setPosition(int x, int y) {
		rect.x = x;
		rect.y = y;
	}
}
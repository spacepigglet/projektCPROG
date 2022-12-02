#include "Component.h"

namespace tower {

	Component::Component(int x, int y, int w, int h, int leftX, int upperY, int rightX , int lowerY) :rect{ x,y,w,h }
	{
	}


	Component::~Component()
	{
	}
}
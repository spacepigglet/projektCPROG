#include "MobileComponent.h"

namespace tower {

MobileComponent::MobileComponent(int x, int y, int w, int h) : Component(x,y,w,h) {}

void MobileComponent::horizontalScroll(int toScroll) {
		moveX(-toScroll);
	}

	void MobileComponent::verticalScroll(int toScroll) {
		moveY(toScroll);
	}

  void MobileComponent::setPosition(int x, int y) {
		rect.x = x;
		rect.y = y;
	}

  MobileComponent::~MobileComponent() {}

}
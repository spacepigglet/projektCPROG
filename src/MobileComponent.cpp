#include "MobileComponent.h"

namespace tower {

MobileComponent::MobileComponent(int x, int y, int w, int h, std::string img) : Component(x,y,w,h), image(img) {}

void MobileComponent::horizontalScroll(int toScroll) {
		moveX(-toScroll);
	}

	void MobileComponent::verticalScroll(int toScroll) {
		moveY(toScroll);
	}

	void MobileComponent::scroll(bool horizontal, int toScroll){
		if (horizontal)
			horizontalScroll(toScroll);
		else
			verticalScroll(toScroll);
	}

  void MobileComponent::setPosition(int x, int y) {
		rect.x = x;
		rect.y = y;
	}

  MobileComponent::~MobileComponent() {}
  

}
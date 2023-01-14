#ifndef MOBILECOMPONENT_H
#define MOBILECOMPONENT_H

#include "Component.h"
#include <string>

namespace tower {
class MobileComponent : public Component {
  public:

  virtual void draw() const = 0;
  virtual void scroll(bool horizontal, int toScroll);
  

  void setPosition(int, int);
  void moveY(int toMove){rect.y += toMove;}
	void moveX(int toMove){rect.x += toMove;}
  virtual void handleCollision(MobileComponent*) {}
  ~MobileComponent();

  protected:
  MobileComponent(int, int, int, int, std::string);

  private:
  virtual void verticalScroll(int);
  virtual void horizontalScroll(int);
  std::string image;

};

}

#endif
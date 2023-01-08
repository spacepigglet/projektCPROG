#ifndef MOBILECOMPONENT_H
#define MOBILECOMPONENT_H

#include "Component.h"

namespace tower {
class MobileComponent : public Component {
  public:

  virtual void draw() const = 0;

  virtual void verticalScroll(int);
  virtual void horizontalScroll(int);

  void setPosition(int, int);
  void moveY(int toMove){rect.y += toMove;}
	void moveX(int toMove){rect.x += toMove;}
  virtual void handleCollision(MobileComponent*) {}
  virtual bool isAlive() {return alive;}
  ~MobileComponent();

  protected:
  MobileComponent(int, int, int, int);

  private:
  bool alive = true;

};

}

#endif
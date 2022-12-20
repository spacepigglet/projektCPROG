#include "ImmobileComponent.h"

namespace tower {

class ImmobileComponent : public Component {

  ImmobileComponent::ImmobileComponent(int x, int y, int w, int h) : Component(x,y,w,h) {}


  ImmobileComponent::~ImmobileComponent() {}

};

}
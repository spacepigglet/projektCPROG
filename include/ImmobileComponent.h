#ifndef IMMOBILECOMPONENT_H
#define IMMOBILECOMPONENT_H

#include "Component.h"

namespace tower {
class ImmobileComponent : public Component {

  public:
  virtual void draw() const = 0;
  ~ImmobileComponent();

  protected:
  ImmobileComponent(int, int, int, int);

};
}
#endif;
#include "Collision.h"

using namespace tower;

bool Collision::collision(Component* a, Component* b) {
  if(a->getLeftX() < b->getRightX() && 
      a->getRightX() > b->getLeftX() && 
      a->getUpperY() < b-> getLowerY() && 
      a->getLowerY() > b->getUpperY()) {
      return true;
  }
    return false;

}

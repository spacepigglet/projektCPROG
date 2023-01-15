#include "Collision.h"

using namespace tower;

/*bool Collision::collision(Component* a, Component* b) {
  if(a == b) {
    return false;
  }
  //std::cout << "Running collision" << std::endl;
  // if(a->getLeftX() < b->getRightX() && 
  //    a->getRightX() > b->getLeftX() && 
  //    a->getUpperY() < b-> getLowerY() && 
  //    a->getLowerY() > b->getUpperY()) {
        if(a->getLowerY() > b->getUpperY() && 
        a->getLowerY() < b->getLowerY()  && 
        a->getLeftX() < b->getRightX() &&  
        a->getRightX() > b->getLeftX()) {
          return true;
        }
    //} 
    return false;
}*/

bool Collision::collision(Component* a, Component* b) {
  if(a->getLeftX() < b->getRightX() && 
      a->getRightX() > b->getLeftX() && 
      a->getUpperY() < b-> getLowerY() && 
      a->getLowerY() > b->getUpperY()) {
      return true;
  }
    return false;

}

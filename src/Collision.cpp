#include "Collision.h"

using namespace tower;

bool Collision::collision(Component* a, Component* b) {
  if(a == b) {
    return false;
  }
  //std::cout << "Running collision" << std::endl;
  if(a->getLeftX() < b->getRightX() && 
     a->getRightX() > b->getLeftX() && 
     a->getUpperY() < b-> getLowerY() && 
     a->getLowerY() > b->getUpperY()) {
      return true;
    } else {
      return false;
      }
}

bool Collision::collision(const SDL_Rect& recA, const SDL_Rect& recB) {

  // if(recA == recB) {
  //   return false;
  // }
  //std::cout << "Running collision" << std::endl;
  if(
    recA.x + recA.w >= recB.x && 
    recB.x + recB.w >= recA.x &&
    recA.y + recA.h >= recB.y && 
    recB.y + recB.h >= recA.y ) 
    { 
    return true;
    } else {
      return false;
    }
}



// 	bool operator==(const SDL_Rect& a, const SDL_Rect& b)
// {
//     return a.x==b.x && a.y==b.y && a.w==b.w && a.h==b.h;
// }

#ifndef COLLISION_H
#define COLLISION_H
#include <SDL2/SDL.h>
#include "MobileComponent.h"
#include <iostream>

using namespace tower;

class Collision {
  public:
  static bool collision(MobileComponent* a, MobileComponent* b);

};

#endif
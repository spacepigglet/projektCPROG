
#ifndef COLLISION_H
#define COLLISION_H
#include <SDL2/SDL.h>
#include "Component.h"
#include <iostream>

using namespace tower;

class Collision {
  public:
  static bool collision(Component* a, Component* b);
  static bool collisionWithEnemy(Component* a, Component* b);

};

#endif
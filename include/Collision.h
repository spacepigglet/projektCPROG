#ifndef COLLISION_H
#define COLLISION_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <iostream>

using namespace tower;

class Collision {
  public:
    static bool collision(Component* a, Component* b);
};

#endif
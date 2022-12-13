
#ifndef COLLISION_H
#define COLLISION_H
#include <SDL2/SDL.h>
#include "Component.h"
#include <iostream>

using namespace tower;

class Collision {
  public:
  static bool collision(const SDL_Rect& recA, const SDL_Rect& recB);
  static bool collision(Component* a, Component* b);
  //bool operator==(const SDL_Rect& other);
};

#endif
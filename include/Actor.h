#ifndef ACTOR_H
#define ACTOR_H

#include "Component.h"
#include "Constants.h"
#include "System.h"
#include "Platform.h"
#include "Enemy.h"
#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>

namespace tower{
  class Actor : public Component {
    public:
      ~Actor();
      static Actor* getInstance(int x, int y, int w, int h, std::string, int);
      static Actor* getInstance(int x, int y, int w, int h, std::string, int, bool);
      void draw() const;
      void update();
      virtual void jump();
      void hurting();
      void reset();
      void keyDown(const SDL_Event&);
      void keyUp(const SDL_Event&);
      void collisionWithPlatform(Platform*);
      void collisionWithEnemy(Enemy*);
      void handleCollision(Component*);
      const int getHealth() const {return health;}
      const bool isDead() const {return dead;};

    protected:
      Actor(int x, int y, int w, int h, std::string image, int);
      Actor(int x, int y, int w, int h, std::string image, int, bool);
    
    private:
      const static int GRAVITY = 1;
      const int startHealth;
      int health;
      const int startX, startY;
      bool isOnTopOfPlatform = false;
      int dx, dy;
      bool movingRight = false, movingLeft = false, movingUp = false, movingDown = false;
      const int xSpeed = 8;
      bool dead = false;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
      int invincibility = 0;
  };
}
#endif
#ifndef ACTOR_H
#define ACTOR_H


#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>

#include "System.h"
#include "Component.h"
#include "Constants.h"
#include "Platform.h"
#include "Enemy.h"


namespace tower{
  class Actor : public Component {
    public:
      ~Actor();
      static Actor* getInstance(int x, int y, int w, int h, std::string, int);
      static Actor* getInstance(int x, int y, int w, int h, std::string, int, bool);
      void draw() const;
      virtual void update();
      virtual void jump();
      virtual void hurting();
      virtual void reset();
      void keyDown(const SDL_Event&);
      void keyUp(const SDL_Event&);
      virtual void collisionWithPlatform(Platform*);
      virtual void collisionWithEnemy(Enemy*);
      virtual void handleCollision(Component*);
      int getHealth() const {return health;}
      bool isDead() const {return dead;};
      void changeSpeed(int i){speed += i;}

    protected:
      Actor(int x, int y, int w, int h, std::string, int);
      Actor(int x, int y, int w, int h, std::string, int, bool);
    
    private:
      const static int GRAVITY = 1;
      const int startHealth;
      int health;
      const int startX, startY;
      bool isOnTopOfPlatform = false;
      int dx, dy;
      bool movingRight = false, movingLeft = false, movingUp = false, movingDown = false;
      int speed = 8;
      bool dead = false;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
      int invincibility = 0;
  };
}
#endif
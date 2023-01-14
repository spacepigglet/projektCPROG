#ifndef ACTOR_H
#define ACTOR_H
#include "MobileComponent.h"
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
  class Actor : public MobileComponent {
    public:
    ~Actor();
    static Actor* getInstance(int x, int y, int w, int h, std::string image);
    void draw() const;
    void update();
    virtual void jump();
    void hurting();
    void reset();
    void keyDown(const SDL_Event&);
    void keyUp(const SDL_Event&);
    void collisionWithPlatform(Platform*);
    void collisionWithEnemy(Enemy*);
    void handleCollision(MobileComponent*);
    int getHealth() {return health;}
    bool isDead() {return dead;};

    protected:
      Actor(int x, int y, int w, int h, std::string image);
    
    private:
      const static int GRAVITY = 1;
      const int startHealth;
      int health;
      const int startX, startY;
      bool isOnTopOfPlatform = false;
      int dx, dy;
      bool movingRight = false, movingLeft = false, movingUp = false, movingDown = false;
      int xSpeed = 7;
      bool dead = false;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
      int invincibility = 0;

  };
}
#endif
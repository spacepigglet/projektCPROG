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
    virtual void jump();
    void keyDown(const SDL_Event&);
    void keyUp(const SDL_Event&);
    void draw() const;
    void collisionWithPlatform(Platform*);
    void collisionWithEnemy(Enemy*);
    void collisionDetection(Component*);
    void handleCollision(MobileComponent*);
    void update();
    int getHealth() {return health;}
    const static int GRAVITY = 1;
    bool isDead() {return dead;};
    
    
    void reset();
    bool isMovingDown() {return movingDown;}
    void hurting();

    protected:
    Actor(int x, int y, int w, int h, std::string image);
    
    private:
      const int startHealth;
      int health;
      const int startX;
      const int startY;
      bool isOnTopOfPlatform = false;
      int dx;
      int dy;
      bool movingRight = false, movingLeft = false, movingUp = false, movingDown = false;
      int xSpeed = 5;
      bool dead = false;
      //int ySpeed = 5;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
      bool faceRight;
      int invincibility = 0;

  };
}
#endif
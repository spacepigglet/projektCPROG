#ifndef ACTOR_H
#define ACTOR_H
#include "MobileComponent.h"
#include "Component.h"
#include "Constants.h"
#include "System.h"
#include "Platform.h"
#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>

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
    void collisionDetection(Component*);
    void update();
    const static int GRAVITY = 1;
    bool dead = false;
    int health;
    void reset();

    protected:
    Actor(int x, int y, int w, int h, std::string image);
    
    private:
      const int startHealth;
      const int startX;
      const int startY;
      bool isOnTopOfPlatform = false;
      int dxVel;
      int dyVel;
      bool movingRight = false, movingLeft = false, movingUp = false, movingDown = false;
      int speed = 5;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
      bool faceRight;


  };
}
#endif
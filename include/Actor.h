#ifndef ACTOR_H
#define ACTOR_H

#include "Component.h"
#include "Constants.h"
#include "System.h"
#include "Session.h"
#include "Platform.h"
#include <string>
#include <iostream>
#include <SDL2/SDL_image.h>

namespace tower{
  class Actor : public Component {
    public:
    ~Actor();
    static Actor* getInstance(int x, int y, int w, int h, std::string image);
    virtual void jump();
    void keyDown(const SDL_Event&);
    void keyUp(const SDL_Event&);
    void draw() const;
    //void update() const;
    void collisionWithPlatform(Platform* p);
    void collisionDetection(Component*);
    void update();
    const static int GRAVITY = 1;

    protected:
    Actor(int x, int y, int w, int h, std::string image);
    
    private:
    //bool canBeControlledByPlayer;
      bool isOnTopOfPlatform = false;
      int dxVel;
      int old_dxVel;
      int dyVel;
      bool movingRight = false, movingLeft = false, movingUp = false, movingDown = false;
      int speed = 10;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
      bool faceRight;


  };
}
#endif
#ifndef ACTOR_H
#define ACTOR_H

#include "Component.h"
#include <string>
#include "Session.h"
#include <vector>
#include "Platform.h"

namespace tower{
  class Actor : public Component {
    public:
    ~Actor();
    static Actor* getInstance(int x, int y, int w, int h, std::string image);
    virtual void jump();
    void keyDown(const SDL_Event&);
    void draw() const;
    bool handleCollisionWithPlatform(Platform*) const;
    void collisionDetection(Component*);

    protected:
    Actor(int x, int y, int w, int h, std::string image);
    
    private:
    //bool canBeControlledByPlayer;
      float speed = 5;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;

  };
}
#endif
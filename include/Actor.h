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
    bool collisionCheckPlatform(const Platform* other) const;
    Component* collisionDetection (const std::vector<Component*>);   // (const Session);

    protected:
    Actor(int x, int y, int w, int h, std::string image);
    
    private:
    //bool canBeControlledByPlayer;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
      int upperLeftX;
      int upperLeftY;
      int lowerRightX;
      int lowerRightY;
  };
}
#endif
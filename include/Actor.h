#ifndef ACTOR_H
#define ACTOR_H

#include "Component.h"
#include <string>
namespace tower{
  class Actor : public Component {
    public:
    static Actor* getInstance(int x, int y, int w, int h, std::string image);
    //using Sprite::Sprite;
    virtual void jump();
    void keyDown(const SDL_Event&);
    void draw() const;

    protected:
    Actor(int x, int y, int w, int h, std::string image);
    ~Actor();
    private:
    //bool canBeControlledByPlayer;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
  };
}
#endif
#ifndef ACTOR_H
#define ACTOR_H

#include "Component.h"
#include <string>
namespace tower{
  class Actor : public Component {
    public:
    ~Actor();
    static Actor* getInstance(int x, int y, int w, int h, std::string image);
    virtual void jump();
    void keyDown(const SDL_Event&);
    void draw() const;
    //void collision(const Component*);

    protected:
    Actor(int x, int y, int w, int h, std::string image);
    
    private:
    //bool canBeControlledByPlayer;
      SDL_Texture* texture;
      std::string image;
      bool isJumping = false;
  };
}
#endif
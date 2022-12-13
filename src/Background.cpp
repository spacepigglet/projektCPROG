#include "Background.h"
#include <string>
#include "Component.h"
#include <SDL2/SDL_image.h>
#include "Constants.h"


namespace tower{

  Background::Background(int x, int y, int w, int h, std::string image) : Component(x, y, w, h) {
    texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
  }
  
  Background:: ~Background(){
        SDL_DestroyTexture(texture);
    }

  Background* Background::getInstance(int x, int y, int w, int h, std::string image){
        return new Background(x, y, w, h, image);
    }


 /*void Background::update() {
  moveY(scrollSpeed);
  }*/

  void Background::scroll(int toScroll) {
    if(getUpperY() >= getHight()){
      setPosition(0, -getHight());
    } else
        moveY(toScroll);

  }

  void Background::draw() const {
    SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
  }
};


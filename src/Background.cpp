#include "Background.h"

namespace tower{

  Background::Background(int x, int y, int w, int h, std::string image) : MobileComponent(x, y, w, h, image) {
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

  void Background::verticalScroll(int toScroll) {
    if(getUpperY() >= getHeight()){
      setPosition(0, -getHeight());
    } else
        moveY(toScroll);

  }

  void Background::horizontalScroll(int toScroll) {
    if(getRightX() <= 0){
      setPosition(getWidth(), 0);
    } else
        moveX(-toScroll);

  }

  void Background::draw() const {
    SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
  }
};


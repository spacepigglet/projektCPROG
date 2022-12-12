#include "Background.h"
#include "Actor.h"
#include <iostream>
#include <string>
#include "Component.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "Constants.h"
#include "System.h"
#include <vector>
#include "Platform.h"
#include "Session.h"
#include "Collision.h"

namespace tower{

  Background::Background(int x, int y, int w, int h, std::string image) : Component(x, y, w, h) {
    texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
  }


  Background* Background::getInstance(int x, int y, int w, int h, std::string image){
        return new Background(x, y, w, h, image);
    }


 /*void Background::update() {
  moveY(scrollSpeed);
  }*/

  void Background::scroll() {


  }

  void Background::draw() const {

  }
};


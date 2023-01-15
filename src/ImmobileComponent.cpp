#include "ImmobileComponent.h"

namespace tower {


  ImmobileComponent::ImmobileComponent(int x, int y, int w, int h, std::string img, bool scrollable) : Component(x,y,w,h,scrollable) {
    texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + img).c_str() );
  }
  ImmobileComponent::ImmobileComponent(int x, int y, int w, int h, std::string img) : Component(x,y,w,h) {
    ImmobileComponent(x,y,w,h,img,true);
  }

  ImmobileComponent* ImmobileComponent::getInstance(int x, int y, int w, int h, std::string img){
    return new ImmobileComponent(x, y, w, h, img);
  }

  ImmobileComponent* ImmobileComponent::getInstance(int x, int y, int w, int h, std::string img, bool scrollable){
    return new ImmobileComponent(x, y, w, h, img, scrollable);
  }

  void ImmobileComponent::draw() const{
    SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
  }

  ImmobileComponent::~ImmobileComponent() {
    SDL_DestroyTexture(texture);
  } 

}
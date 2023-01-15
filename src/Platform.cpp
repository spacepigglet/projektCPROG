#include "Platform.h"
#include "Enemy.h"

namespace tower{
    
    Platform::Platform(int x, int y, int w, int h, std::string image) : Component(x,y,w,h), isToBeRemoved(false) { // x, y, (x+w), (y+h+1)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath_images + image).c_str() );
    }
    
    Platform::Platform(int x, int y, int w, int h, std::string image, bool toRemove, bool scrollable) : Component(x,y,w,h, scrollable), isToBeRemoved(toRemove) { // x, y, (x+w), (y+h+1)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath_images + image).c_str() );
    }

    Platform* Platform::getInstance(int x, int y, int w, int h, std::string image){
        return new Platform(x, y, w, h, image);
    }

    Platform* Platform::getInstance(int x, int y, int w, int h, std::string image, bool removable, bool scrollable){
      return new Platform(x, y, w, h, image, removable, scrollable);
    }

    void Platform:: draw() const {
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
    }

    Platform:: ~Platform(){
      SDL_DestroyTexture(texture);
    }

    void Platform::update() {
      //if scrolling vertically
      if(getUpperY() > WINDOW_HEIGHT + getHeight()) {
        newX = rand() % (WINDOW_WIDTH - getRightX()); //randomize new position within limits
        newY = -getHeight();
        setPosition(newX, newY);
      }

      //if scrolling horizontally
      else if(getRightX() < 0) {
        newX = WINDOW_WIDTH;
        newY = rand() % (WINDOW_WIDTH - getRightX());

        setPosition(newX, newY);
       
      }
    }

}
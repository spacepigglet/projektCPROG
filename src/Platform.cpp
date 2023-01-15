#include "Platform.h"
#include "Enemy.h"

namespace tower{
    
    Platform::Platform(int x, int y, int w, int h, std::string image) : Component(x,y,w,h), isToBeRemoved(false) { // x, y, (x+w), (y+h+1)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    Platform::Platform(int x, int y, int w, int h, std::string image, bool toRemove) : Component(x,y,w,h), isToBeRemoved(toRemove) { // x, y, (x+w), (y+h+1)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    Platform::Platform(int x, int y, int w, int h, std::string image, bool toRemove, bool scrollable) : Component(x,y,w,h, scrollable), isToBeRemoved(toRemove) { // x, y, (x+w), (y+h+1)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    Platform* Platform::getInstance(int x, int y, int w, int h, std::string image){
        return new Platform(x, y, w, h, image);
    }

    Platform* Platform::getInstance(int x, int y, int w, int h, std::string image, bool removable){
        return new Platform(x, y, w, h, image, removable);
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

    void Platform::collisionDetection(const Component* other){
        
    }

    void Platform::update() {
      if(getUpperY() > WINDOW_HEIGHT + getHeight()) {
        newX = rand() % (WINDOW_WIDTH - getRightX());
        newY = -getHeight();
        setPosition(newX, newY);
    
      }

      //Om man inte scrollar vertikalt kommer aldrig koden ovan att köras
      //Plattformarna hamnar för nära varandra i y led
      else if(getRightX() < 0) {
        newX = WINDOW_WIDTH;
        newY = rand() % (WINDOW_WIDTH - getRightX());

        setPosition(newX, newY);
       
      }
    }

}
#include "Platform.h"
#include "Enemy.h"

namespace tower{
    
    Platform::Platform(int x, int y, int w, int h, std::string image) : MobileComponent(x,y,w,h) { // x, y, (x+w), (y+h+1)
		texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + image).c_str() );
    }

    Platform* Platform::getInstance(int x, int y, int w, int h, std::string image){
        return new Platform(x, y, w, h, image);
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
      if(getUpperY()+50 > WINDOW_HEIGHT + getWidth()) { //bredden på plattform, gör till variabel
        newX = rand() % (WINDOW_WIDTH - getRightX());
        newY = -getHeight();
        //int newX = rand() % (WINDOW_WIDTH - this->getRightX());

        setPosition(newX, newY); //höjd på plattform, gör till variabel
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
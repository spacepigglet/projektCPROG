#include "Platform.h"

namespace tower{
    
    Platform::Platform(int x, int y, int w, int h, std::string image) : Component(x,y,w,h) { // x, y, (x+w), (y+h+1)
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

}
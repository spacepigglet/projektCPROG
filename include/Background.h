#ifndef BACKGROUND_H
#define BACKGROUND_H


#include "Component.h"
#include <string>
#include  "System.h"
#include <SDL2/SDL_image.h>
#include "Constants.h"

namespace tower {
  class Background : public Component {

    public:
      ~Background();
      static Background* getInstance(int x, int y, int w, int h, std::string image);
      //void update();
      void draw() const;
      void verticalScroll(int);
      void horizontalScroll(int);
      SDL_Texture* get_bg_tex() const {return texture;};

    protected:
      Background(int x, int y, int w, int h, std::string image);
    
    private:
      SDL_Texture* texture;
      std::string image;
  };
}


#endif
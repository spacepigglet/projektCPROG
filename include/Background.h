#ifndef BACKGROUND_H
#define BACKGROUND_H

#include  "System.h"
#include "Component.h"
#include "Constants.h"
#include <string>
#include <SDL2/SDL_image.h>

namespace tower {
  class Background : public Component {

    public:
      ~Background();
      static Background* getInstance(int x, int y, int w, int h, std::string image);
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
#ifndef IMMOBILECOMPONENT_H
#define IMMOBILECOMPONENT_H

#include "Component.h"
#include "Constants.h"
#include "System.h"
#include <string>
#include <SDL2/SDL_image.h>

namespace tower {
class ImmobileComponent : public Component {

  public:
    void draw() const;
    ~ImmobileComponent();
    static ImmobileComponent* getInstance(int, int, int, int, std::string);
    static ImmobileComponent* getInstance(int, int, int, int, std::string, bool);

  protected:
    ImmobileComponent(int, int, int, int, std::string); 
    ImmobileComponent(int, int, int, int, std::string, bool); 

  private:
    SDL_Texture* texture;

};
}
#endif
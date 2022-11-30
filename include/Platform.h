#ifndef PLATFORM_H
#define PLATFORM_H
#include "Component.h"
#include <string>

namespace tower{
    class Platform : public Component{
    public:
    static Platform* getInstance(int x, int y, int w, int h, std::string image);
    void draw() const;
    void collision(const Component*);
    ~Platform();

    protected:
    Platform(int x, int y, int w, int h, std::string image);
    
    private:
    SDL_Texture* texture;
    std::string image;
    };
}
#endif
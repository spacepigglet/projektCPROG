#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include <SDL2/SDL.h> 

class Sprite {
  
  public:
    Sprite(int x, int y, std::string image); //takes in path to the pictures
    void moveUp(const int steg = 1);
    void moveDown(const int steg = 1);
    void moveRight(const int steg = 1);
    void moveLeft(const int steg = 1);
    const int getX() const;
    const int getY() const;

    SDL_Rect getRect();
    SDL_Texture getTexture();

  private:
    std::string image;
    int gx;
    int gy;
    SDL_Rect rect;
    SDL_Texture* texture;
};

#endif
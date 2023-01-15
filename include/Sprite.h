#ifndef SPRITE_H
#define SPRITE_H
#include <string>
#include <SDL2/SDL.h> 

class Sprite {
  
  public:
    Sprite(int x, int y, std::string image); //takes in path to the pictures
    void moveUp(int steg = 1);
    void moveDown(int steg = 1);
    void moveRight(int steg = 1);
    void moveLeft(int steg = 1);
    int getX();
    int getY();

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
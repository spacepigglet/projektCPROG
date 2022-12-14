#include "Constants.h"
#include "Button.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <SDL2/SDL_image.h>

namespace tower {

	Button::Button(int x, int y, int w, int h, std::string txt):Component(x,y,w,h)
	{
		SDL_Surface* surf = TTF_RenderText_Solid(sys.get_font(), txt.c_str(), { 0,0,0 });
		texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
		buttonIcon = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/marble.jpg").c_str() );
		//downIcon = IMG_LoadTexture(sys.get_ren(), (constants::gResPath + "images/marble.jpg").c_str() );
	}

	Button::~Button()
	{
		SDL_DestroyTexture(texture);
		SDL_DestroyTexture(buttonIcon);
		
	}

	Button* Button::getInstance(int x, int y, int w, int h, std::string txt) {
		return new Button(x, y, w, h, txt);
	}

	void Button::mouseDown(const SDL_Event& eve) {
		SDL_Point p = { eve.button.x, eve.button.y };
		if (SDL_PointInRect(&p, &getRect()))
			isDown = true;
	}
	void Button::mouseUp(const SDL_Event& eve) {
		SDL_Point p = { eve.button.x, eve.button.y };
		if (SDL_PointInRect(&p, &getRect()) && isDown)
			perform(this);

		isDown = false;
	}
	void Button::draw() const {
		
		SDL_RenderCopy(sys.get_ren(), buttonIcon, NULL, &getRect());

		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());

	}
}
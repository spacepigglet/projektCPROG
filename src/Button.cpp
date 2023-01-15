#include "Constants.h"
#include "Button.h"
#include "System.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

namespace tower {

	Button::Button(int x, int y, int w, int h, std::string txt, bool scrollable):Component(x,y,w,h, scrollable) {
		SDL_Surface* surf = TTF_RenderText_Solid(sys.get_font(), txt.c_str(), { 0,0,0 });
		text_texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
		buttonIcon_texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath_images + "marble.jpg").c_str() );
	}

	Button::Button(int x, int y, int w, int h, std::string txt):Component(x,y,w,h) {
		Button(x,y,w,h,txt, txt, true);
	}

	Button::Button(int x, int y, int w, int h, std::string txt, std::string image, bool scrollable):Component(x,y,w,h, scrollable) {
		SDL_Surface* surf = TTF_RenderText_Solid(sys.get_font(), txt.c_str(), { 0,0,0 });
		text_texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
		buttonIcon_texture = IMG_LoadTexture(sys.get_ren(), (constants::gResPath_images + image).c_str() );
	
	}

	Button::Button(int x, int y, int w, int h, std::string txt, std::string image):Component(x,y,w,h) {
		Button(x,y,w,h,txt, image, true);
	}

	Button::~Button() {
		SDL_DestroyTexture(text_texture);
		SDL_DestroyTexture(buttonIcon_texture);
	}

	Button* Button::getInstance(int x, int y, int w, int h, std::string txt) {
		return new Button(x, y, w, h, txt);
	}

	Button* Button::getInstance(int x, int y, int w, int h, std::string txt, bool scrollable) {
		return new Button(x, y, w, h, txt, scrollable);
	}

	Button* Button::getInstance(int x, int y, int w, int h, std::string txt, std::string image, bool scrollable) {
		return new Button(x, y, w, h, txt, image,scrollable);
	}

	Button* Button::getInstance(int x, int y, int w, int h, std::string txt, std::string image) {
		return new Button(x, y, w, h, txt, image);
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
		SDL_RenderCopy(sys.get_ren(), buttonIcon_texture, NULL, &getRect());
		SDL_RenderCopy(sys.get_ren(), text_texture, NULL, &getRect());
	}
}
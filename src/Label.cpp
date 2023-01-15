#include "Label.h"
#include <SDL2/SDL_ttf.h>
#include "System.h"
#include <iostream>
#include <string>

using namespace std;

namespace tower {

	Label* Label::getInstance(int x, int y, int w,
		int h, std::string txt, SDL_Color c) 
	{
		return new Label(x, y, w, h, txt, c);
	}

	Label::Label(int x, int y, int w, int h, std::string txt, SDL_Color c): Component(x,y,w,h), text(txt), color(c)
	{
		SDL_Surface* surf = TTF_RenderText_Solid(sys.get_font(), text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
	}

	string Label::getText() const {
		return text;
	}
	void Label::setText(std::string newText) {
		text = newText;
		SDL_DestroyTexture(texture);
		SDL_Surface* surf = TTF_RenderText_Solid(sys.get_font(),
			text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
	}

	void Label::setColor(SDL_Color newColor) {
		color = newColor;
		SDL_DestroyTexture(texture);
		SDL_Surface* surf = TTF_RenderText_Solid(sys.get_font(),
			text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(sys.get_ren(), surf);
		SDL_FreeSurface(surf);
	}

	void Label::draw() const {
		SDL_RenderCopy(sys.get_ren(), texture, NULL, &getRect());
	}

	Label::~Label()
	{
		SDL_DestroyTexture(texture);
	}
	
	
}
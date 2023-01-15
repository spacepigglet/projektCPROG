#ifndef LABEL_H
#define LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>

#include "Component.h"
#include "System.h"

namespace tower {

	class Label: public Component {
	public:
		static Label* getInstance(int x, int y, int w, int h, std::string txt, SDL_Color color);
		static Label* getInstance(int x, int y, int w, int h, std::string txt, SDL_Color color, bool scrollable);
		void draw() const;
		std::string getText() const;
		void setText(std::string newText);
		~Label();
		SDL_Color getColor() const {return color;}
		void setColor(SDL_Color c);
	
	protected:
		Label(int, int, int, int, std::string , SDL_Color);
		Label(int, int, int, int, std::string , SDL_Color, bool scrollable);
	
	private:
		std::string text;
	  SDL_Color color;
		SDL_Texture* texture;
	};

}
#endif
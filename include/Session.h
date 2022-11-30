#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include "Component.h"

namespace tower {

	class Session
	{
	public:
		Session();
		void add(Component* c);
		void run();
		~Session();
		const std::vector<Component*> getComps() const {return comps;}
		void processInput();
		void updateGame();
		void generateOutput();
	private:
		std::vector<Component*> comps;
		bool quit;
	};
}
#endif
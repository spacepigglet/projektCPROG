#include "Session.h"

namespace tower {
    class Game {
    public:
        Game (Session);
        ~Game();
        void start();
    private:
        Session* org_ses;
        int counter;
        //bool playing = true;
    };
}
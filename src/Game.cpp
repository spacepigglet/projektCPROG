#include "Game.h"
#include <string>
using namespace std;
namespace tower {
    Game::Game (Session session) : org_ses(&session){
        cout << "***Game::Game()" << endl;
        start();
    }
    Game::~Game(){
        cout << "***Game::~Game()" << endl;
    }
    void Game::start() {
        bool playing = true;
        while (playing){
            Session* current_ses = org_ses;
            counter +=1 ;
            cout << counter << endl;
            playing = current_ses->run();

        }
    }
}


#include "Game.h"
#include "Gaming.h"


using namespace Gaming;

void Game::populate(){

    //TODO
}
Game::Game(){

    //TODO
}
// note: manual population by default
Game::Game(unsigned width, unsigned height, bool manual = true){

    //TODO
}
Game::Game(const Game &another){

    //TODO

}

// getters
unsigned int Game::getNumPieces() const{
    //TODO
}
unsigned int Game::getNumAgents() const{
    //TODO
}
unsigned int Game::getNumSimple() const{
    //TODO
}
unsigned int Game::getNumStrategic() const{
    //TODO
}
unsigned int Game::getNumResources() const{
    //TODO
}
const Piece *Game::getPiece(unsigned int x, unsigned int y) const{
    //TODO
}

// grid population methods
void Game::addSimple(const Position &position){
    //TODO
}
// used for testing only
void Game::addSimple(const Position &position, double energy){//TODO

}
void Game::addSimple(unsigned x, unsigned y){//TODO

}
void Game::addSimple(unsigned x, unsigned y, double energy){//TODO

}
void Game::addStrategic(const Position &position, Strategy *s = new DefaultAgentStrategy()){//TODO

}
void Game::addStrategic(unsigned x, unsigned y, Strategy *s = new DefaultAgentStrategy()){//TODO

}
void Game::addFood(const Position &position){//TODO

}
void Game::addFood(unsigned x, unsigned y){//TODO

}
void Game::addAdvantage(const Position &position){//TODO

}
void Game::addAdvantage(unsigned x, unsigned y){//TODO

}
const Surroundings Game::getSurroundings(const Position &pos) const{//TODO

}

// gameplay methods
// note: STAY by default
static const ActionType reachSurroundings(const Position &from, const Position &to){//TODO

}

bool Game::isLegal(const ActionType &ac, const Position &pos) const{//TODO

}
const Position Game::move(const Position &pos, const ActionType &ac) const{//TODO

} // note: assumes legal, use with isLegal()
void Game::round(){//TODO

}   // play a single round
void Game::play(bool verbose = false){//TODO

}    // play game until over

//        const Agent &winner(); // what if no winner or multiple winners?

// Print as follows the state of the game after the last round:
//
// Round 1:
// [F0   ][     ][T1   ]
// [W2   ][     ][F3   ]
// [     ][S4   ][     ]
// Status: Playing...
//
// Round 5:
// [     ][     ][     ]
// [     ][T1   ][     ]
// [     ][     ][     ]
// Status: Over!
//
std::ostream &operator<<(std::ostream &os, const Game &game){//TODO

}
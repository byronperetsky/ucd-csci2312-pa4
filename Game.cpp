

#include "Game.h"
#include "Gaming.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"


using namespace Gaming;

Game::NUM_INIT_AGENT_FACTOR = 4;
Game::NUM_INIT_RESOURCE_FACTOR = 2;
Game::MIN_WIDTH = 3;
Game::MIN_HEIGHT = 3;
Game::STARTING_AGENT_ENERGY = 20;
Game::STARTING_RESOURCE_CAPACITY = 10;


PositionRandomizer Game::__posRandomizer = PositionRandomizer();


void Game::populate(){

    std::default_random_engine gen;
    std::uniform_int_distribution<int> d(0, __width * __height);

    __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;

    __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;

    unsigned int numStrategic = __numInitAgents / 2;

    unsigned int numSimple = __numInitAgents - numStrategic;

    unsigned int numAdvantages = __numInitResources / 4;

    unsigned int numFoods = __numInitResources - numAdvantages;



    // populate Strategic agents
    while (numStrategic > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Strategic(*this, pos, Game::STARTING_AGENT_ENERGY);
            numStrategic --;
        }
    }

    while (numSimple > 0) {
        int i = d(gen);
        if (i != (__width * __height) && __grid[i] == nullptr) {
            Position pos(i / __width, i % __width);
            __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
            numSimple--;
        }
    }

    while (numSimple > 0) {
        int i = d(gen);
        if (i != (__width * __height) && __grid[i] == nullptr) {
            Position pos(i / __width, i % __width);
            __grid[i] = new Advantage(*this, pos, STARTING_AGENT_ENERGY);
            numSimple--;
        }
    }

    while (numSimple > 0) {
        int i = d(gen);
        if (i != (__width * __height) && __grid[i] == nullptr) {
            Position pos(i / __width, i % __width);
            __grid[i] = new Food(*this, pos, STARTING_AGENT_ENERGY);
            numSimple--;
        }
    }


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

Game::~Game(){
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
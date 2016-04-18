#include <iomanip>
#include <set>
#include "Game.h"
#include "Simple.h"
#include "Strategic.h"
#include "Advantage.h"
#include "Food.h"


using namespace Gaming;


PositionRandomizer Game::__posRandomizer;

const unsigned  int Game::NUM_INIT_AGENT_FACTOR = 4;
const unsigned int Game::NUM_INIT_RESOURCE_FACTOR = 2;
const unsigned int Game::MIN_WIDTH = 3;
const unsigned int Game::MIN_HEIGHT = 3;
const double Game::STARTING_AGENT_ENERGY = 20;
const double Game::STARTING_RESOURCE_CAPACITY = 10;


void Game::populate() {


    __numInitAgents = (__width * __height) / NUM_INIT_AGENT_FACTOR;
    __numInitResources = (__width * __height) / NUM_INIT_RESOURCE_FACTOR;
    unsigned int numStrategic = __numInitAgents / 2;
    unsigned int numSimple = __numInitAgents - numStrategic;
    unsigned int numAdvantages = __numInitResources / 4;
    unsigned int numFoods = __numInitResources - numAdvantages;

    std::default_random_engine gen;
    std::uniform_int_distribution<int> d(0, __width * __height-1);



    while (numStrategic > 0) {
        int i = d(gen);// random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Strategic(*this, pos, STARTING_AGENT_ENERGY);
            numStrategic --;
        }
    }

    while (numSimple > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Simple(*this, pos, STARTING_AGENT_ENERGY);
            numSimple --;
        }
    }
    while (numAdvantages > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Advantage(*this, pos, STARTING_RESOURCE_CAPACITY);
            numAdvantages --;
        }
    }
    while (numFoods > 0) {
        int i = d(gen); // random index in the grid vector
        if (__grid[i] == nullptr) { // is position empty
            Position pos(i / __width, i % __width);
            __grid[i] = new Food(*this, pos, STARTING_RESOURCE_CAPACITY);
            numFoods --;
        }
    }

}

Game::Game() {


    __numInitAgents = 0;
    __numInitResources = 0;
    __width = 3;
    __height = 3;
    __round = 0;
    __status = NOT_STARTED ;
    __verbose = false;

    for (int i = 0; i < __width*__height; ++i) {
        __grid.push_back(nullptr) ;
    }

}

Game::Game(unsigned width, unsigned height, bool manual) {


    if(width < MIN_WIDTH || height < MIN_HEIGHT)
    {
        throw InsufficientDimensionsEx(MIN_WIDTH,MIN_HEIGHT,width,height);
    }

    __numInitAgents = 0;
    __numInitResources = 0;
    __width = width;
    __height = height;
    __verbose = false;
    __status = NOT_STARTED;
    __round = 0;

    for (int i = 0; i < __width*__height; ++i) {
        __grid.push_back(nullptr) ;
    }

    if(!manual)
    {
        populate();
    }

}

Game::Game(const Game &another) {
    //TODO???
}

Game::~Game() {

    for (int index = 0; index  < __grid.size(); ++index ) {

        if (__grid[index ] != nullptr)
        {
            delete __grid[index ];
        }

    }
}

unsigned int Game::getNumPieces() const {

    return getNumAgents()+getNumResources();
}

unsigned int Game::getNumAgents() const {

    return getNumSimple()+getNumStrategic();
}

unsigned int Game::getNumSimple() const {

    unsigned int gnSimple = 0;

    for (int index = 0; index < __grid.size(); ++index) {

        if(__grid[index]!= nullptr)
        {
            if (__grid[index]->getType() == SIMPLE)
            {
                gnSimple ++;
            }

        }
    }

    return gnSimple;
}

unsigned int Game::getNumStrategic() const {

    unsigned int gnStrat=0;

    for (int index = 0; index < __grid.size(); ++index) {

        if(__grid[index]!= nullptr)
        {
            if (__grid[index]->getType() == STRATEGIC)
            {
                gnStrat++;
            }

        }
    }


    return gnStrat;
}

unsigned int Game::getNumResources() const {

    unsigned int gnRes=0;

    for (int index = 0; index < __grid.size(); ++index) {

        if(__grid[index]!= nullptr)
        {
            if (__grid[index]->getType() == FOOD || __grid[index]->getType() == ADVANTAGE)
            {
                gnRes++;
            }

        }
    }
    return gnRes;
}

const Piece *Game::getPiece(unsigned int x, unsigned int y) const {

    if(__grid[((x*__width)+y)] != nullptr)
    {
        return __grid[((x*__width)+y)];
    }

    throw PositionEmptyEx(x,y);
}

void Game::addSimple(const Position &position) {

    Simple *newSimple = new Simple(*this,position,STARTING_AGENT_ENERGY);

    __grid[position.x*__width + position.y] = newSimple;
}

void Game::addSimple(const Position &position, double energy) {

    Simple *newSimple = new Simple(*this,position,energy);

    __grid[position.x*__width + position.y] = newSimple;

}

void Game::addSimple(unsigned x, unsigned y) {

    Position p(x,y);

    this->addSimple(p);
}

void Game::addSimple(unsigned x, unsigned y, double energy) {

    Position p(x,y);
    this->addSimple(p,energy);
}

void Game::addStrategic(const Position &position, Strategy *s) {

    Strategic *newStrat = new Strategic(*this,position,STARTING_AGENT_ENERGY,s);

    __grid[position.x*__width + position.y] = newStrat;
}

void Game::addStrategic(unsigned x, unsigned y, Strategy *s) {

    Position p(x,y);

    this->addStrategic(p,s);
}

void Game::addFood(const Position &position) {

    Food *newFood = new Food(*this,position,STARTING_RESOURCE_CAPACITY);

    __grid[position.x*__width + position.y] = newFood;
}

void Game::addFood(unsigned x, unsigned y) {

    Position p(x,y);

    this->addFood(p);
}

void Game::addAdvantage(const Position &position) {

    Advantage *newAdvent = new Advantage(*this,position,STARTING_RESOURCE_CAPACITY);

    if((position.x*__width + position.y)>__grid.size())
    {
        throw OutOfBoundsEx(__width,__height,position.x,position.y);
    }

    __grid[position.x*__width + position.y] = newAdvent ;
}

void Game::addAdvantage(unsigned x, unsigned y) {

    Position p(x,y);

    this->addAdvantage(p);
}

const Surroundings Game::getSurroundings(const Position &pos) const {

    Surroundings area;

    int x = pos.x-1;

    for (int i = 0; i < 3; ++i) {

        int y = pos.y-1;

        for (int j = 0; j < 3; ++j) {

            if(((x * __width) + y)==((pos.x*__width)+pos.y))
            {
                area.array[(i * 3) + j] = SELF;
            }
            else if(x < 0 ||x >__height-1 || y<0 || y > __width-1)
            {
                area.array[(i * 3) + j] = INACCESSIBLE;
            }
            else if (__grid[(x * __width) + y] == nullptr)
            {
                area.array[(i * 3) + j] = EMPTY;
            }
            else
            {
                area.array[(i * 3) + j] = __grid[(x * __width) + y]->getType();
            }

            y++;
        }

        x++;
    }

    return area;
}

const ActionType Game::reachSurroundings(const Position &from, const Position &to) {

    ActionType around = STAY;

    int xVar = to.x-from.x;
    int yVar = to.y-from.y;

    if(xVar == -1 && yVar == -1)
    {
        around = NW;
    }
    else if(xVar == -1 && yVar == 0)
    {
        around = N;
    }
    else if(xVar == -1 && yVar == 1)
    {
        around =NE;
    }
    else if(xVar == 0 && yVar == -1)
    {
        around =W;
    }
    else if(xVar == 0 && yVar == 0)
    {
        around =STAY;
    }
    else if(xVar == 0 && yVar == 1)
    {
        around =E;
    }
    else if(xVar == 1 && yVar == -1)
    {
        around =SW;
    }
    else if(xVar == 1 && yVar == 0)
    {
        around =S;
    }
    else if(xVar == 1 && yVar == 1)
    {
        around =SE;
    }


    return around;
}

bool Game::isLegal(const ActionType &ac, const Position &pos) const {


    Surroundings checkSurr = getSurroundings(pos);

    std::vector <ActionType> direction = {NW,N,NE,W,STAY,E,SW,S,SE};

    int directionSub = 0;
    bool check;

    for (int index = 0; index < direction.size(); ++index) {

        if(direction[index]== ac)
        {
            directionSub = index;

            break;
        }
    }

    check = checkSurr.array[directionSub] != INACCESSIBLE;

    return check;

}

const Position Game::move(const Position &pos, const ActionType &ac) const {

    Position movePos;

    if(ac == NW)
    {
        movePos = Position(pos.x-1,pos.y-1);
    }
    else if(ac == N)
    {
        movePos = Position(pos.x-1,pos.y);
    }
    else if(ac == NE)
    {
        movePos = Position(pos.x-1,pos.y+1);
    }
    else if(ac == W)
    {
        movePos = Position(pos.x,pos.y-1);
    }
    else if(ac == STAY)
    {
        movePos = Position(pos.x,pos.y);
    }
    else if(ac == E)
    {
        movePos = Position(pos.x,pos.y+1);
    }
    else if(ac == SW)
    {
        movePos = Position(pos.x+1,pos.y-1);
    }
    else if(ac == S)
    {
        movePos = Position(pos.x+1,pos.y);
    }
    else if(ac == SE)
    {
        movePos = Position(pos.x+1,pos.y+1);
    }

    return movePos;
}

void Game::round() {

    std::set<Piece*> pieces;

    for (auto it = __grid.begin(); it != __grid.end(); ++it) {

        if (*it) { pieces.insert(pieces.end(), *it); (*it)->setTurned(false); }

    }

    for (auto item = pieces.begin(); item != pieces.end(); ++item) {

        if (!(*item)->getTurned())
        {

            (*item)->setTurned(true);

            (*item)->age();

            ActionType ac = (*item)->takeTurn(getSurroundings((*item)->getPosition()));

            Position posA = (*item)->getPosition();

            Position posB = move(posA, ac);

            if (posA.x != posB.x || posA.y != posB.y) { Piece *mPiece = __grid[posB.y + (posB.x * __width)];

                if (mPiece) {

                    //(*(*item)) * (*p);

                    if ((*item)->getPosition().x != posA.x || (*item)->getPosition().y != posA.y) {
                        __grid[posB.y + (posB.x * __width)] = (*item); __grid[posA.y + (posA.x * __width)] = mPiece; }
                }
                else {

                    (*item)->setPosition(posB);

                    __grid[posB.y + (posB.x * __width)] = (*item);

                    __grid[posA.y + (posA.x * __width)] = nullptr;

                }
            }
        }
    }

    for (unsigned int i = 0; i < __grid.size(); ++i) {

        if (__grid[i] && !(__grid[i]->isViable()))
        {
            { delete __grid[i]; __grid[i] = nullptr; }
        }

    }

    if (getNumResources() <= 0) { __status = Status::OVER; }

    ++__round;


}

void Game::play(bool verbose) {
    __verbose = verbose;
    round();
    if(getNumPieces()>1 && getNumResources() > 0) {
        play(verbose);
    }
}

std::ostream & Gaming::operator<<(std::ostream &os, const Game &game) {

    os << "Round " << game.__round << std::endl;

    for (int index = 0; index < game.__height; ++index) {

        for (int indexB = 0; indexB < game.__width; ++indexB) {

            os << '[' << std::setw(5) << std::left << *game.__grid[index*game.__width + indexB] << ']';

        }

        os << std::endl;
    }

    if(game.__status == Game::NOT_STARTED)
    {
        os << "Status: Not Started...";
    }
    else if(game.__status == Game::PLAYING)
    {
        os << "Status: Playing...";
    }
    else
    {
        os << "Status: Over!";
    }

    return os;
}
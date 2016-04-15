#include <iomanip>
#include <sstream>

#include "Strategic.h"


using namespace Gaming;

const char Strategic::STRATEGIC_ID = 'T';

Strategic::Strategic(const Game &g, const Position &p, double energy, Strategy *s) : Agent(g, p, energy) {
    __strategy = s;
}

Strategic::~Strategic(){

    delete __strategy;
}

void Strategic::print(std::ostream &os) const{

    std::string printStr;

    printStr = std::to_string(__id);

    std::stringstream ss;

    ss << STRATEGIC_ID;
    ss << printStr;

    std::getline(ss, printStr);

    for (int index = 0; index < printStr.length() ; ++index) {

       os << printStr[index];

    }

}

ActionType Strategic::takeTurn(const Surroundings &s) const{

    return (*__strategy)(s);

}
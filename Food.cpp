#include <sstream>
#include "Food.h"

using namespace Gaming;

const char Food::FOOD_ID = 'F';
Food::Food(const Game &g, const Position &p, double capacity):Resource(g,p,capacity) {

}

Food::~Food() {

}

void Food::print(std::ostream &os) const {

    std::string s;
    std::stringstream ss;

    ss << FOOD_ID << __id;

    getline(ss,s);
    os << s;

}
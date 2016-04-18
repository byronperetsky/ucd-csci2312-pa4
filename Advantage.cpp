#include <sstream>

#include "Advantage.h"




using namespace Gaming;

const char Advantage::ADVANTAGE_ID = 'D';
const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;

Advantage::Advantage(const Game &g, const Position &p, double capacity) : Resource(g, p, capacity) {

}

Advantage::~Advantage() {

}


void Advantage::print(std::ostream &os) const {

    std::string pOut;
    std::stringstream ss;


    pOut = std::to_string(__id);

    ss << Advantage::ADVANTAGE_ID;
    ss << pOut;


    std::getline(ss, pOut);

    for (int index = 0; index < pOut.length(); ++index) {
        os << pOut[index];
    }
}

double Advantage::getCapacity() const {

    return __capacity*ADVANTAGE_MULT_FACTOR;
}

double Advantage::consume() {

    double temp = getCapacity();
    __capacity = 0;
    finish();
    return (temp);
}


#include "Resource.h"

using namespace Gaming;

const double Resource::RESOURCE_SPOIL_FACTOR = 1.2;

Resource::Resource(const Game &g, const Position &p, double capacity) : Piece(g, p), __capacity(capacity) {

}

Resource::~Resource() {}

double Resource::consume() {

    double conTem = __capacity;
    this->__capacity = 0;

    finish();

    return conTem;
}

void Resource::age(){

    __capacity -= RESOURCE_SPOIL_FACTOR;

    if (__capacity <= 0) finish();

}

ActionType Resource::takeTurn(const Surroundings &s) const {

    return STAY;//Resources haven't any feet.

}

Piece &Resource::operator*(Piece &other) {

    return *this;
}

Piece &Resource::interact(Agent *) {

    return *this;
}

Piece &Resource::interact(Resource *) {

    return *this;
}
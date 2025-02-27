#include "Piece.h"

using namespace Gaming;

unsigned int Piece::__idGen = 1;

Piece::Piece(const Game &g, const Position &p):__game(g) {
    __id = __idGen;
    __idGen++; // increment so it will be ready for next one.
    __finished = false; // initially not finishend
    __turned = false;
    __position = p;


}

Piece::~Piece() {
// nothing to delete
}

std::ostream & Gaming::operator<<(std::ostream &os, const Piece &piece) {
    if(&piece != nullptr)
        piece.print(os);
    else
        os << "";
    return os;
}


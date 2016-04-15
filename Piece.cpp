#include "Piece.h"
#include "Agent.h"
#include "Resource.h"
#include "Simple.h"
#include "Strategic.h"
#include "Food.h"
#include "Advantage.h"

using namespace Gaming;

Piece::Piece(const Game &g, const Position &p){
    //TODO
}
Piece::~Piece(){
    //TODO
}

std::ostream &operator<<(std::ostream &os, const Piece &piece);
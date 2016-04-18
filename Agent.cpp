#include "Agent.h"
#include "Advantage.h"
#include "Food.h"

using namespace Gaming;

const double Agent::AGENT_FATIGUE_RATE = 0.3;

Agent::Agent(const Game &g, const Position &p, double energy): Piece(g,p) {

    __energy = energy;

}

Agent::~Agent() {

}

void Agent::age() {

    __energy -= AGENT_FATIGUE_RATE;


}

Piece &Agent::operator*(Piece &other) {

    Agent *otherA = dynamic_cast<Agent*>(&other);
    Resource *otherR = dynamic_cast<Resource*>(&other);


    if(otherA)
    {

        return this->interact(otherA);
    }

    if(otherR)
    {
        return  this->interact(otherR);
    }

    return *this;
}

Piece &Agent::interact(Agent * other) {

    if(__energy > other->__energy)
    {
        __energy -= other->__energy;
        other->__energy = 0;
        other->finish();
    }
    else if (__energy < other->__energy)
    {
        other->__energy -=__energy;
        __energy = 0;
        finish();
    }
    else
    {
        __energy = 0.0;
        other->__energy = 0.0;
        finish();
        other->finish();
    }

    return *this;
}

Piece &Agent::interact(Resource * other) {

    this->addEnergy(other->consume());

    return *this;
}
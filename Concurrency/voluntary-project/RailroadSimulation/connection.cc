#include "connection.hh"

using namespace Util;
using namespace std;
using namespace Rinn;

Rinn::Connection::Connection(Direction d, unsigned length, std::shared_ptr<Rinn::Location> dest)
{
    this->dir = d;
    this->length = length;
    this->destination = dest;

    steps = make_shared<TrackSteps>();

    for(unsigned int i = 0; i < length; i++) {
        shared_ptr<recursive_mutex> step = make_shared<recursive_mutex>();
        steps.get()->push_back(step);
    }
}

Util::Direction Rinn::Connection::getDirection()
{
    return dir;
}

unsigned Rinn::Connection::getLength()
{
    return length;
}

std::shared_ptr<Rinn::Location> Rinn::Connection::getDestinationLocation()
{
    return destination;
}

shared_ptr<TrackSteps> Connection::getSteps()
{
    return steps;
}

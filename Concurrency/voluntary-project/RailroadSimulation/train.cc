#include "train.hh"

using namespace Rinn;
using namespace std;
using namespace Util;


Train::Train(string name)
{
    this->name = name;
}

const std::string Train::getName()
{
    return name;
}

shared_ptr<Location> Train::getCurrentLocation()
{
    return location;
}

void Train::arriveAt(std::shared_ptr<Location> newLocation)
{
    location = newLocation;
}

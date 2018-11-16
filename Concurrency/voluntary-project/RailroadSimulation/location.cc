#include "location.hh"

using namespace Rinn;
using namespace std;
using namespace Util;

Location::Location(std::string desc)
{
    description = desc;
}

const string Location::getDescription()
{
    return description;
}

#include "railroadjunction.hh"

using namespace Rinn;
using namespace std;
using namespace Util;

RailroadJunction::RailroadJunction(string desc) : Location(desc)
{
    connections = make_shared<vector<shared_ptr<Connection>>>();
    trafficControl = make_shared<map<Direction, shared_ptr<TrafficStatus>>>();
}

void RailroadJunction::lockOppositeDirection(Location* origin)
{
    // Find the traffic control object whose destination is "origin"
    for(shared_ptr<Connection> conn : *connections) {
        if(conn.get()->getDestinationLocation().get()->getDescription() == origin->getDescription()) {  // description is unique
            shared_ptr<TrafficStatus> status = trafficControl.get()->find(conn.get()->getDirection())->second;
            status.get()->inOpposite();

            break;
        }
    }
}

void RailroadJunction::unlockOppositeDirection(Location* origin)
{
    // Find the traffic control object whose destination is "origin"
    for(shared_ptr<Connection> conn : *connections) {
        if(conn.get()->getDestinationLocation().get()->getDescription() == origin->getDescription()) { // description is unique
            shared_ptr<TrafficStatus> status = trafficControl.get()->find(conn.get()->getDirection())->second;
            status.get()->outOpposite();

            break;
        }
    }
}

void RailroadJunction::initializeTrafficControl()
{
    for(auto dir : getPossibleDirections()){
        trafficControl.get()->insert(make_pair(dir, make_shared<TrafficStatus>()));
    }
}

shared_ptr<Location> RailroadJunction::moveToNextLocation(Direction d)
{
    shared_ptr<TrafficStatus> status = trafficControl.get()->find(d)->second; // Directional traffic controller
    shared_ptr<Connection> connection;

    // Find Connection object for direction
    for(shared_ptr<Connection> conn : *connections) {
        if(conn.get()->getDirection() == d) {
            connection = conn;
            break;
        }
    }

    RailroadJunction* nextJunction = dynamic_cast<RailroadJunction*>(connection.get()->getDestinationLocation().get());

    // Locking
    nextJunction->lockOppositeDirection(this); // In destination junction, opposite direction must be locked to prevent "head-on collisions"
    status.get()->in();

    // Move on tracks
    auto steps = connection.get()->getSteps();
    unsigned length = connection.get()->getLength();

    unsigned int currentStep = 0;
    recursive_mutex* current = nullptr;
    recursive_mutex* previous = nullptr;
    do {
        current = steps.get()->at(currentStep).get();
        current->lock();

        if(previous != nullptr) {
            previous->unlock();
            current->unlock();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        currentStep++;

        if(currentStep < length) { // more steps after this one? Lock the next step before moving on it to prevent other trains from "passing" this one
            recursive_mutex* next = steps.get()->at(currentStep).get();
            next->lock();
            previous = current;
        }
    }while(currentStep < length);

    // Last step, unlock current for the next train!
    current->unlock();

    // release locks
    nextJunction->unlockOppositeDirection(this);
    status.get()->out();

    return connection.get()->getDestinationLocation();
}

void RailroadJunction::addConnectedLocation(Direction d, unsigned length, std::shared_ptr<Location> l)
{
    possibleDirections.push_back(d);
    connections.get()->push_back(make_shared<Connection>(d, length, l));
}

vector<Direction> RailroadJunction::getPossibleDirections()
{
    return possibleDirections;
}

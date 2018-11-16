#include "constants.h"
#include "location.hh"
#include "railroadjunction.hh"
#include "trafficstatus.hh"
#include "train.hh"

#include <time.h>

#include <memory>
#include <chrono>
#include <thread>
#include <string>

using namespace Rinn;
using namespace std;
using namespace Util;

#define NUMBER_OF_TRAINS 5

void runTrain(string name, shared_ptr<RailroadJunction> startJunction) {

    Train tr(name);
    tr.arriveAt(startJunction);

    while(true) {
        Direction d;
        auto directions = tr.getCurrentLocation().get()->getPossibleDirections();
        int randomIndex = randomMinMax(0, 2); // all junctions have 3 possible directions
        d = directions[randomIndex];

        auto nextLocation = tr.getCurrentLocation().get()->moveToNextLocation(d); // calling moveToNextLocation will handle all locking/unlocking of directions and waiting

        print(tr.getName() + " moved from " + tr.getCurrentLocation().get()->getDescription() +  " to " + nextLocation.get()->getDescription());

        tr.arriveAt(nextLocation);
        std::this_thread::sleep_for(std::chrono::milliseconds(randomMinMax(10,5000))); // train stops at a junction for a while
    }

}

int main()
{
    srand(time(NULL));
    vector<shared_ptr<RailroadJunction>> junctions;

    shared_ptr<RailroadJunction> j1 = make_shared<RailroadJunction>("Pohjoinen risteys 1");
    shared_ptr<RailroadJunction> j2 = make_shared<RailroadJunction>("Keskimmäinen risteys 2");
    shared_ptr<RailroadJunction> j3 = make_shared<RailroadJunction>("Eteläinen risteys 3");
    shared_ptr<RailroadJunction> j4 = make_shared<RailroadJunction>("Itäinen risteys 4");

    junctions.push_back(j1);
    junctions.push_back(j2);
    junctions.push_back(j3);
    junctions.push_back(j4);

    j1.get()->addConnectedLocation(LEFT, 45, j3);
    j1.get()->addConnectedLocation(RIGHT, 30, j4);
    j1.get()->addConnectedLocation(DOWN, 10, j2);

    j2.get()->addConnectedLocation(UP, 10, j1);
    j2.get()->addConnectedLocation(DOWN, 10, j3);
    j2.get()->addConnectedLocation(RIGHT, 25, j4);

    j3.get()->addConnectedLocation(UP, 10, j2);
    j3.get()->addConnectedLocation(LEFT, 45, j1);
    j3.get()->addConnectedLocation(RIGHT, 30, j4);

    j4.get()->addConnectedLocation(UP, 30, j1);
    j4.get()->addConnectedLocation(DOWN, 30, j3);
    j4.get()->addConnectedLocation(LEFT, 25, j2);

    j1.get()->initializeTrafficControl();
    j2.get()->initializeTrafficControl();
    j3.get()->initializeTrafficControl();
    j4.get()->initializeTrafficControl();

    vector<thread> threads;

    for(unsigned i = 1; i <= NUMBER_OF_TRAINS; i++) {
        auto startingJunction = junctions.at(randomMinMax(0, 3));
        string name("Juna ");
        name.append(to_string(i));
        threads.push_back(thread(runTrain, name, startingJunction));
    }

    for( auto& thread : threads) {
        thread.join();
    }

}

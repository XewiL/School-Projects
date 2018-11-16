#include "trafficstatus.hh"

using namespace std;
using namespace Rinn;
using namespace Util;

TrafficStatus::TrafficStatus()
{
    wait = false;
    inCount = 0;
    inOppositeCount = 0;
}

void TrafficStatus::in()
{
    unique_lock<mutex> lck(lock);
    if(wait) {  // wait-flag: someone is waiting for their turn to move from the opposite direction
        waitlock.wait(lck, [this]{ return !wait;});
        incrementInCounter();
        waitlock.notify_one();
    } else {
        waitlock.notify_one();
        incrementInCounter();
    }
}

void TrafficStatus::out()
{
    //unique_lock<mutex> lck(lock);
    decrementInCounter();
}

void TrafficStatus::inOpposite()
{
    unique_lock<mutex> lck(lock);
    if(inCount > 0) {
        wait = true;
        directionalLock.wait(lck, [this]{ return inCount == 0;});
        incrementOppositeInCounter();
        directionalLock.notify_one();
    } else {
        directionalLock.notify_one();
        incrementOppositeInCounter();
    }

}

void TrafficStatus::outOpposite()
{
    //unique_lock<mutex> lck(lock);
    decrementOppositeInCounter();
}

void TrafficStatus::incrementInCounter()
{
    unique_lock<mutex> lck(counterLock);
    inCount++;
}

void TrafficStatus::decrementInCounter()
{
    unique_lock<mutex> lck(counterLock);
    if(inCount > 0) { // overflow check
       inCount--;
    }

    if(inCount == 0) {
        directionalLock.notify_one();
    }
}

void TrafficStatus::incrementOppositeInCounter()
{
    unique_lock<mutex> lck(counterLock);
    inOppositeCount++;
}

void TrafficStatus::decrementOppositeInCounter()
{
    unique_lock<mutex> lck(counterLock);
    if(inOppositeCount > 0) { // overflow check
        inOppositeCount--;
    }

    if(inOppositeCount == 0) {
        wait = false;
        waitlock.notify_one();
    }
}

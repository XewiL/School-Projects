#ifndef RAILROADJUNCTION_HH
#define RAILROADJUNCTION_HH

#include "constants.h"

#include <map>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>

#include "train.hh"
#include "trafficstatus.hh"
#include "connection.hh"

namespace Rinn {

/**
     * @brief The RailroadJunction class
     * Describes a railroad junction, a subclass of Location.
     */
    class RailroadJunction : public Location
    {
    public:
        RailroadJunction(std::string desc);
        virtual ~RailroadJunction() = default;

        /**
         * @brief lockOppositeDirection Lock the opposite direction to prevent head-on collisions.
         * @param origin The location from which this function was called, the direction which will be locked.
         */
        void lockOppositeDirection(Rinn::Location* origin);

        /**
         * @brief unlockOppositeDirection After movement between junctions is complete, this is called to let other trains move to the opposite direction.
         * @param origin The location from which the movement originated, the direction which will be unlocked.
         */
        void unlockOppositeDirection(Rinn::Location* origin);

        /**
         * @brief initializeTrafficControl Called once after connections are added, this will initialize a map of Directions and TrafficControl objects.
         */
        void initializeTrafficControl();

    private:
        std::vector<Util::Direction> possibleDirections;
        std::shared_ptr<std::vector<std::shared_ptr<Rinn::Connection>>> connections;
        std::shared_ptr<std::map<Util::Direction, std::shared_ptr<Rinn::TrafficStatus>>> trafficControl;

        // Location interface
    public:
        std::shared_ptr<Location> moveToNextLocation(Util::Direction d);
        void addConnectedLocation(Util::Direction d, unsigned length, std::shared_ptr<Location> l);
        std::vector<Util::Direction> getPossibleDirections();
    };

}

#endif // RAILROADJUNCTION_HH

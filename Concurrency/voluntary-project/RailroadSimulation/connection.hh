#ifndef CONNECTION_HH
#define CONNECTION_HH

#include <memory>
#include "constants.h"
#include "location.hh"

namespace Rinn {

typedef std::vector<std::shared_ptr<std::recursive_mutex>> TrackSteps;

/**
 * @brief The Connection class
 * Describes a connection from one Location to another.
 */
class Connection
    {

    public:
        Connection(Util::Direction d, unsigned length, std::shared_ptr<Rinn::Location> dest);
        ~Connection() = default;

        /**
         * @brief getDirection
         * @return Direction of this Connection from the perspective of the owner.
         */
        Util::Direction getDirection();

        /**
         * @brief getLength
         * @return Length (in arbitrary units) of connection.
         */
        unsigned getLength();

        /**
         * @brief getDestinationLocation
         * @return Destination Location
         */
        std::shared_ptr<Rinn::Location> getDestinationLocation();

        /**
         * @brief getSteps
         * @return A vector of recursive mutexes, to be iterated over to simulate moving.
         */
        std::shared_ptr<TrackSteps> getSteps();
    private:
        std::shared_ptr<TrackSteps> steps;
        Util::Direction dir;
        unsigned length;
        std::shared_ptr<Rinn::Location> destination;
    };
}
#endif // CONNECTION_HH

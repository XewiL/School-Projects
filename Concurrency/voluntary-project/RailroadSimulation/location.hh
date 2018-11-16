#ifndef LOCATION_HH
#define LOCATION_HH

#include <vector>
#include <memory>

#include "location.hh"
#include "constants.h"

namespace Rinn {

    /**
     * @brief The Location class
     * Describes a Location in the railroad network.
     */
    class Location
    {
    public:
        Location(std::string description);
        virtual ~Location() = default;

        /**
         * @brief addConnectedLocation Add a connected location to this Location
         * @param d Direction of the destination location, from the perspective of THIS Location.
         * @param length Length of the connection between this and the other location (arbitrary units)
         * @param l Destination Location object
         */
        virtual void addConnectedLocation(Util::Direction d, unsigned length, std::shared_ptr<Location> l) = 0;

        /**
         * @brief moveToNextLocation Simulates movement between Locations, to a Direction.
         * @param d Direction to move towards. Should be one of the possible directions.
         * @return The destination Location object
         */
        virtual std::shared_ptr<Location> moveToNextLocation(Util::Direction d) = 0;

        /**
         * @brief getPossibleDirections
         * @return A vector of all possible movement directions for this Location
         */
        virtual std::vector<Util::Direction> getPossibleDirections() = 0;

        /**
         * @brief getDescription
         * @return A unique description for this Location
         */
        const std::string getDescription();

    protected:
        std::string description;
    };

}

#endif // LOCATION_HH

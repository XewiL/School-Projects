#ifndef TRAIN_HH
#define TRAIN_HH

#include "constants.h"

#include "location.hh"

#include <memory>

namespace Rinn {

/**
     * @brief The Train class
     * Describes a train that moves between junctions in the simulation.
     */
    class Train
    {
    public:
        Train(std::string name);
        ~Train() = default;

        /**
         * @brief getName
         * @return Unique name of this train object
         */
        const std::string getName();

        /**
         * @brief getCurrentLocation
         * @return Current Location of this train
         */
        std::shared_ptr<Rinn::Location> getCurrentLocation();

        /**
         * @brief arriveAt Sets the current location of this train
         * @param newLocation
         */
        void arriveAt(std::shared_ptr<Rinn::Location> newLocation);
    private:
        std::string name;
        std::shared_ptr<Rinn::Location> location;
    };

}
#endif // TRAIN_HH

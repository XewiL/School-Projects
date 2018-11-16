#ifndef TRAFFICSTATUS_HH
#define TRAFFICSTATUS_HH

#include <memory>
#include <map>
#include <mutex>
#include <condition_variable>

#include "constants.h"

namespace Rinn {
/**
     * @brief The TrafficStatus class
     * Handles traffic control for a direction in a junction.
     */
    class TrafficStatus
    {
    public:
        TrafficStatus();
        ~TrafficStatus() = default;

        /**
         * @brief in Increment in counter for the direction which is associated with this object.
         * This is called when the opposite direction in the destination junction is locked, and train is ready to move.
         */
        void in();

        /**
         * @brief out Decrement in counter for the direction which is associated with this object.
         * This is called when the train has "arrived" in the destination junction.
         */
        void out();

        /**
         * @brief inOpposite Increment opposite in counter. Opposite in counter keeps track of trains moving in the opposite direction, i.e. towards the junction where this object is located.
         */
        void inOpposite();

        /**
         * @brief outOpposite Decrement opposite in counter.
         */
        void outOpposite();

        /* Following functions are same as above, but synchronized with a different lock.*/

        void incrementInCounter();
        void decrementInCounter();

        void incrementOppositeInCounter();
        void decrementOppositeInCounter();

    private:
        std::mutex lock;
        std::mutex counterLock;

        std::condition_variable directionalLock;
        std::condition_variable waitlock;
        bool wait;
        unsigned inCount;
        unsigned inOppositeCount;
    };
}
#endif // TRAFFICSTATUS_HH

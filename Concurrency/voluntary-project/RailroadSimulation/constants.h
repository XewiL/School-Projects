#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <mutex>
#include <iostream>
#include <random>

namespace Util{

    static std::mutex printlock;

    /**
     * @brief The Direction enum
     * Contains all possible directions to which one can proceed from a junction
     */
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    /**
     * @brief print - synchronized print to cout.
     * @param text Text to print to console
     */
    static void print(std::string text) {
        printlock.lock();
        std::cout << text << std::endl;
        printlock.unlock();
    }

    /**
     * @brief randomMinMax - Thread-local random number generator.
     * @param min
     * @param max
     * @return Random integer between min and max.
     */
    static int randomMinMax(int min, int max)
    {
        //thread_local std::mt19937 generator(std::random_device{}());
       // //std::uniform_int_distribution<int> distribution(min, max);
        //return distribution(generator);
        static std::default_random_engine re {};
        using Dist = std::uniform_int_distribution<int>;
        static Dist uid {};
        return uid(re, Dist::param_type{min,max});
    }

}


#endif // CONSTANTS_H

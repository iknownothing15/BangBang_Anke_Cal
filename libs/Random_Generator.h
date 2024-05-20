#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H
#include "Consts.h"
#include <random>
#include <ctime>
class Random_Generator
{
private:
    std::mt19937_64 generator;

public:
    Random_Generator()
    {
        #ifdef _WIN32
        generator = std::mt19937_64(time(NULL));
        #else 
        generator = std::mt19937_64(std::random_device()());
        #endif
    }
    int get_random(const int &l, const int &r)
    {
        return std::uniform_int_distribution<int>(l, r)(generator);
    }
    /**
     * @brief Get the result of a coc like check. 1 is the greatest success, >=96 is the greatest failure.
     * 
     * @param standard the standard of the check.
     * @return int The id of the result.
     */
    int get_result(const double &standard)
    {
        int result = get_random(1, 100);
        if (result <= 1)
            return GREATEST_SUCCESS_ID;
        if (result >= 96)
            return GREATEST_FAILURE_ID;
        if (result * 5 <= standard)
            return VERY_HARD_SUCCESS_ID;
        if (result * 2 <= standard)
            return HARD_SUCCESS_ID;
        if (result * 1 <= standard)
            return NORMAL_SUCCESS_ID;
        return FAILURE_ID;
    }
};
#endif
#pragma once

#include <iostream>
#include <random>
#include <limits>

static std::random_device randSrc;
static std::uniform_int_distribution<int> randGen(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
static std::uniform_int_distribution<int> positiveRandGen(0, std::numeric_limits<int>::max());

class Rand {

    public: 
        static int getInt();
        static int getPositiveInt();
};
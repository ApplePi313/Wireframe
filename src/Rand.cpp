#include "Rand.hpp"

int Rand::getInt() {
    return randGen(randSrc);
}

int Rand::getPositiveInt() {
    return positiveRandGen(randSrc);
}
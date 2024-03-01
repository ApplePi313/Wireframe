#include "Rand.hpp"

int Rand::getInt() {
    return randGen(randSrc);
}

int Rand::getPositiveInt() {
    return positiveRandGen(randSrc);
}

bool Rand::chance(int chance) {
    return getPositiveInt() % 100 < chance;
}
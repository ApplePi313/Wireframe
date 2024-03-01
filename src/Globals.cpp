#include "Globals.hpp"

using namespace Globals;

const int Globals::mini(int arg1, int arg2) {
    return arg1 < arg2 ? arg1 : arg2;
}

const float Globals::minf(float arg1, float arg2) {
    return arg1 < arg2 ? arg1 : arg2;
}

const int Globals::maxi(int arg1, int arg2) {
    return arg1 > arg2 ? arg1 : arg2;
}

const float Globals::maxf(float arg1, float arg2) {
    return arg1 > arg2 ? arg1 : arg2;
}
#include "Globals.hpp"

using namespace Globals;

int Globals::windowWidth = 0;
int Globals::windowHeight = 0;
const float PI = 3.141592653589793;

const long Globals::currTimeMillis() {
    return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now()).time_since_epoch().count();
}

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
#pragma once

#include <iostream>
#include <chrono>
#include <cmath>

namespace Globals {
    struct Coord {
        float x;
        float y;

        Coord() {
            x = 0.0;
            y = 0.0;
        }
        Coord(float xPos, float yPos) {
            x = xPos;
            y = yPos;
        }

        inline Coord operator+(Coord c) {
            return {x + c.x, y + c.y};
        }
        inline void operator+=(Coord c) {
            x += c.x;
            y += c.y;
        }
        inline Coord operator*(float v) {
            return {x * v, y * v};
        }
        inline bool operator==(Coord c) {
            return x == c.x && y == c.y;
        }
    };
    extern int windowWidth;
    extern int windowHeight;
    extern float PI;

    extern const long currTimeMillis();

    extern const int mini(int, int);
    extern const float minf(float, float);
    extern const int maxi(int, int);
    extern const float maxf(float, float);
}
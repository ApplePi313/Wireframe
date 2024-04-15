#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <cmath>

namespace Globals {
    extern int windowWidth;
    extern int windowHeight;
    extern std::fstream attrFInStrm;
    extern std::fstream shaderFInStrm;
    extern const float PI;

    struct Coord {
        int x;
        int y;

        Coord() {
            x = 0;
            y = 0;
        }
        Coord(int xPos, int yPos) {
            x = xPos;
            y = yPos;
        }

        float magnitude() {
            return hypot(x, y);
        }
        float angle() {
            if (x < 0) {
                return 360 - ((atan(y / x) * 180/PI) + 90);
            } else if (x == 0) {
                return y > 0 ? 180 : 0;
            } else {
                return 90 - ((atan(y / x) * 180/PI));
            }
        }

        void print() {
            std::cout << "x: " << x << "\n";
            std::cout << "y: " << y << "\n";
        }

        inline Coord operator+(Coord c) {
            return {x + c.x, y + c.y};
        }
        inline Coord operator-(Coord c) {
            return {x - c.x, y - c.y};
        }
        inline void operator+=(Coord c) {
            x += c.x;
            y += c.y;
        }
        inline Coord operator*(float v) {
            return {(int) (x * v), (int) (y * v)};
        }
        inline Coord operator/(float v) {
            return {(int) (x / v), (int) (y / v)};
        }
        inline bool operator==(Coord c) {
            return x == c.x && y == c.y;
        }
    };

    extern const long currTimeMillis();

    extern const int mini(int, int);
    extern const float minf(float, float);
    extern const int maxi(int, int);
    extern const float maxf(float, float);
}
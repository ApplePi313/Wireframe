#pragma once 

#include <iostream>
#include "Globals.hpp"

/*
    Hitbox types:
    0: does nothing
    1: blocks movement
    2: damages
    3: blocks movement & damages
    4: kills
*/

using namespace Globals;

class Hitbox {
        Coord coords;

        int width = 0;
        int height = 0;

        int type = 0;

        int modifier = 0;

    public:
        Hitbox();
        Hitbox(Coord, int, int); // x, y, width, height
        Hitbox(Coord, int, int, int); // x, y, width, height, type
        Hitbox(Coord, int, int, int, int); // x, y, width, height, types, modifier(for damage type amount of damage, more functionality to be added)

        int getX();
        void setX(int);

        int getY();
        void setY(int);

        void setCoords(Coord);
        Coord getCoords();
        void translate(Coord);

        int getWidth();
        void setWidth(int);

        int getHeight();
        void setHeight(int);

        void setDimensions(int, int);

        int getType();
        void setType(int);

        int getModifier();
        void setModifier(int);

        void setInteractiveProperties(int, int);

        bool isColliding(Hitbox);
        bool isBlocking();
};

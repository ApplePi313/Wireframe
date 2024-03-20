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

        float width = 0.0f;
        float height = 0.0f;

        int type = 0;

        int modifier = 0;

    public:
        Hitbox();
        Hitbox(Coord, float, float); // x, y, width, height
        Hitbox(Coord, float, float, int); // x, y, width, height, type
        Hitbox(Coord, float, float, int, int); // x, y, width, height, types, modifier(for damage type amount of damage, more functionality to be added)

        float getX();
        void setX(float);

        float getY();
        void setY(float);

        void setCoords(Coord);

        float getWidth();
        void setWidth(float);

        float getHeight();
        void setHeight(float);

        void setDimensions(float, float);

        int getType();
        void setType(int);

        int getModifier();
        void setModifier(int);

        void setInteractiveProperties(int, int);

        bool isColliding(Hitbox);
        bool isBlocking();
};

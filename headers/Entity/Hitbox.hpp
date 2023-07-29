#pragma once 

#include <iostream>

/*
    Hitbox types:
    0: does nothing
    1: blocks movement
    2: damages
    3: kills
*/

class Hitbox {
    float width;
    float height;

    int type = 0;

    int modifier = 0;

    float xPos = 0.0f;
    float yPos = 0.0f;

    public: 
        Hitbox();
        Hitbox(float, float, float, float); // x, y, width, height
        Hitbox(float, float, float, float, int); // x, y, width, height, type
        Hitbox(float, float, float, float, int, int); // x, y, width, height, types, modifier(for damage type amount of damage, more functionality to be added)

        void resize(float, float);
        void setType(int);
        void setModifier(int);
        void setInteractiveProperties(int, int);
};
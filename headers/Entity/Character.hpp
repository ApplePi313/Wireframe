#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <limits>

#include "AttributesParser.hpp"

#include "Shaders/Shader.hpp"

#include "Entity/Entity.hpp"
#include "Entity/Hitbox.hpp"
#include "Entity/Bullet.hpp"
#include "Globals.hpp"

/* Error Codes
    0: fine
    1: failed file read
    2: Failed to read vertices/indices
    3: invalid setup of the attribute file
*/

using namespace Globals;

class Character : public Entity {
    float bulletRotation = 0.0;

    public: 
        Character();
        Character(const char*, const char*, const char*, float, Coord);
            // character attribute file,  vshader, fshader, character size, xPos, yPos
        void setup(const char*, const char*, const char*, float, Coord);

        void getVertices(float**, int*);
        void getIndices(unsigned int**, int*);

        int getErrorCode();

        Bullet shoot(int, Coord);

        void set1f(const char*, float);
        void set2f(const char*, float, float);
        void set3f(const char*, float, float, float);
        void set4f(const char*, float, float, float, float);

        void set1i(const char*, int);
        void set2i(const char*, int, int);
        void set3i(const char*, int, int, int);
        void set4i(const char*, int, int, int, int);
};

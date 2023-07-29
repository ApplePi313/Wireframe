#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include <limits>

#include "Shaders/Shader.hpp"
#include "Entity/Bullet.hpp"
#include "AttributesParser.hpp"

/* Error Codes
    0: fine
    1: failed file read
    2: Failed to read vertices/indices
    3: invalid setup of the attribute file
*/

class Character {
    int error = 0;

    float width = 0.0f;

    AttributesParser attributesParser;

    Shader shader;

    Bullet bullets[100];


    public: 
        Character();
        Character(const char*, const char*, const char*, float);

        void setup(const char*, const char*, const char*, float);

        void getVertices(float**, int*);
        void getIndices(unsigned int**, int*);

        int getErrorCode();

        void shoot(int);

        // These all just call programs in the Shader class
        void activateShader();
        
        void draw();

        void set1f(const char*, float);
        void set2f(const char*, float, float);
        void set3f(const char*, float, float, float);
        void set4f(const char*, float, float, float, float);

        void set1i(const char*, int);
        void set2i(const char*, int, int);
        void set3i(const char*, int, int, int);
        void set4i(const char*, int, int, int, int);
};

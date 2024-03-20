#pragma once

#include <iostream>

#include "Templates/SignalReceiver.hpp"
#include "Shaders/Shader.hpp"
#include "Globals.hpp"

using namespace signals;
using namespace Globals;

class Bullet : public SignalReceiver {
    Coord coords;

    float velocityMagnitude = 0.0f;
    float rotation = 0.0f;

    Coord velocity;

    float vX = 0.0f;
    float vY = 0.0f;

    long spawnTime = 0;
    long lastUpdateTime = 0;
    long lifespan = 0;

    float strokeWidth = 2.0f;

    float* vertices;
    unsigned int* indices;

    int verticesLen;
    int indicesLen;

    public: 
        Bullet();
        Bullet(Coord, float, float, long, float, float*, int, unsigned int*, int); // x, y, v, rot, life
        void setup(Coord, float, float, long, float, float*, int, unsigned int*, int);

        void clear();
        Signal signal(Signal);
        void draw(Shader*);
};

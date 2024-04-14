#pragma once

#include <iostream>

#include "Templates/SignalReceiver.hpp"
#include "Entity/Entity.hpp"
#include "Shaders/Shader.hpp"
#include "Globals.hpp"

using namespace signals;
using namespace Globals;

class Bullet : public Entity {
    float velocityMagnitude = 0.0f;
    float rotation = 0.0f;

    float vX = 0.0f;
    float vY = 0.0f;

    long spawnTime = 0;
    long lifespan = 0;

    public: 
        Bullet();
        Bullet(Coord, float, Coord, float, long, const char*); // x, y, v, rot, life, attr
        void setup(Coord, float, Coord, float, long, const char*);

        Signal signal(Signal);
        void draw(Shader*);
};

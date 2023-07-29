#pragma once

#include <iostream>
#include <ctime>
#include <cmath>

class Bullet {
    float xPos = 0.0f;
    float yPos = 0.0f;

    float velocity = 0.0f;
    float rotation = 0.0f;

    long spawnTime = 0;
    int lifespan = 0;

    bool dead = true;

    const float PI = 3.141592653589793;

    public: 
        Bullet();
        Bullet(float, float, float, float, int);
        void setup(float, float, float, float, int);

        void update();

        void clear();
        bool isDead();
};

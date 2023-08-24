#include <iostream>

#include "World/Room.hpp"

#include "Entity/Hitbox.hpp"

#include "Rand.hpp"

class Level {
    float xPos = 0;
    float yPos = 0;

    int tileWidth = 0;
    int tileHeight = 0;

    public:
        Level();
        Level(float, float, int, int);

        void setup(float, float, int, int);

        void setCoords(float, float);
        void checkHitboxInteractions(Hitbox* hitbox);
};

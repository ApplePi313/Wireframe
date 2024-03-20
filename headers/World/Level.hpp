#pragma once

#include <iostream>

#include "World/Tile.hpp"
#include "World/Room.hpp"
#include "World/Hall.hpp"

#include "Entity/Hitbox.hpp"

#include "Rand.hpp"
#include "Globals.hpp"

using namespace Globals;

class Level {
    Coord coords;

    int tileWidth = 0;
    int tileHeight = 0;

    int numVerticalRooms, numHorizontalRooms = 0;

    int rbcWidth, rbcHeight = 10;
    int rbcOffsetX, rbcOffsetY = 0;

    Room** roomsPtr;

    Rand randGen;

    int hallPos;

    const char* vertexShaderFile;
    const char* fragmentShaderFile;

    Tile** tilesPtr;
    Hitbox** hitboxesPtr;

    Shader shader;

    void generate();

    public:
        Level();
        Level(Coord, int, int, const char*, const char*);

        void setup(Coord, int, int, const char*, const char*);

        void draw(Coord);

        void getHitboxes(Hitbox***, int*, int*);

        void setCoords(Coord);
        void checkHitboxInteractions(Hitbox* hitbox);
};

#pragma once

#include <vector>
#include <iostream>

#include "World/Tile.hpp"
#include "World/Room.hpp"
#include "World/Hall.hpp"

#include "Entity/Entity.hpp"
#include "Entity/Character.hpp"
#include "Entity/Hitbox.hpp"

#include "Rand.hpp"
#include "Globals.hpp"

using namespace Globals;

class Level {
    Coord coords;
    Rand randGen;
    Shader shader;
    Character character;
    std::vector<Entity> entities;

    int tileWidth = 0;
    int tileHeight = 0;
    int tileSize = 64;

    int numVerticalRooms, numHorizontalRooms = 0;

    int rbcWidth, rbcHeight = 10;
    int rbcOffsetX, rbcOffsetY = 0;

    Room** roomsPtr;

    int hallPos;

    const char* vertexShaderFile;
    const char* fragmentShaderFile;

    Tile** tilesPtr;
    Hitbox** hitboxesPtr;


    void generate();

    public:
        Level();
        Level(Coord, int, int, const char*, const char*);

        void setup(Coord, int, int, const char*, const char*);

        void setCoords(Coord);
        void setCharacter(Character);

        void draw(Coord);

        void getHitboxes(Hitbox***, int*, int*);

        void checkHitboxInteractions(Hitbox* hitbox);

        void moveCharacter(int*, int*);
};

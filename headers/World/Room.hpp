#pragma once

#include <iostream>
#include <cstdint>

#include "World/Tile.hpp"
#include "Shaders/Shader.hpp"
#include "Rand.hpp"
#include "Entity/Hitbox.hpp"
#include "Globals.hpp"

using namespace Globals;

class Room {
    Coord coords;

    int width;
    int height;

    int usableWidth;
    int usableHeight;

    int design = 0; // for now there will only be one design (design 0)

    Tile** tilesPtr;
    Hitbox** hitboxesPtr;

    Shader shader;

    Rand randGen;

    int numBoxes;

    bool boxesAreSeparate = false;

    int* boxesXPtr;
    int* boxesYPtr;

    void generate(int, int);

    public:
        Room();
        Room(Coord, int, int, int, const char*, const char*);
        Room(Coord, int, int, int, Tile**, Hitbox**, int, int);

        void setup(Coord, int, int, int, const char*, const char*);
        void setup(Coord, int, int, int, Tile**, Hitbox**, int, int);

        int formEntry(int, int, int);
        int formEntry(int, int, int, Tile**, Hitbox**, int, int);

        void activateShader();
        void draw(Coord);

        void getHitboxes(Hitbox***, int*, int*);
        void getTiles(Tile***, int*, int*);

        int getWidth();
        int getHeight();

        void close();
};

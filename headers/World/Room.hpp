#pragma once

#include "World/Tile.hpp"
#include "Shaders/Shader.hpp"
#include "Rand.hpp"
#include "Entity/Hitbox.hpp"

class Room {
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

    void generate();

    public:
        Room();
        Room(int, int, int, const char*, const char*);

        void setup(int, int, int, const char*, const char*);

        void activateShader();
        void draw(float x, float y);

        void getHitboxes(Hitbox***, int*, int*);

        void close();
};

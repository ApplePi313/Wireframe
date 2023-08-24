#pragma once

#include <iostream>

#include "World/Tile.hpp"
#include "Shaders/Shader.hpp"
#include "Entity/Hitbox.hpp"



class Hall {
    /*
     * Error Codes:
     * 1: invalid orientation
     */
    int error = 0;

    float xPos = 0.0f;
    float yPos = 0.0f;

    int tileWidth = 0;
    int tileHeight = 0;

    /*
    * Orientations:
    * 0: horizontal
    * 1: vertical
    */
    int orientation = 0;

    Shader shader;

    Tile** tilesPtr;
    Hitbox** hitboxesPtr;

    public:
        Hall();

        Hall(float, float, int, int, int, const char*, const char*); // x, y, tile width, tile height, orientation

        void setup(float, float, int, int, int, const char*, const char*); // x, y, tile width, tile height, orientation

        void draw(float, float);

        void activateShader();

        void getHitboxes(Hitbox***, int*, int*);

        void close();
};

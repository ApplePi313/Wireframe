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

    Coord coords;

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
        Hall(Coord, int, int, int, Tile**, Hitbox**, int, int); // x, y, tile width, tile height, orientation, tiles, hitboxes, tilesOffsetX, tilesOffsetY
        Hall(Coord, int, int, int, const char*, const char*); // x, y, tile width, tile height, orientation

        void altSetup(Coord, int, int, int, Tile**, Hitbox**, int, int); // x, y, tile width, tile height, orientation, tiles, hitboxes, tilesOffsetX, tilesOffsetY
        void setup(Coord, int, int, int, const char*, const char*); // x, y, tile width, tile height, orientation

        void draw(Coord);

        void activateShader();

        void getHitboxes(Hitbox***, int*, int*);

        void close();
};

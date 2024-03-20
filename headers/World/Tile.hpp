#pragma once

#include <string>
#include <iostream>

#include "Shaders/Shader.hpp"
#include "AttributesParser.hpp"
#include "Globals.hpp"

using namespace Globals;

/*
    Designs:
    0: floor
    1: box
    2: wall
*/

/* Error Codes
    1: failed file read
    2: Failed to read vertices/indices
*/

class Tile {
    Coord coords;

    int size = 64; // Tile size in pixels

    int design = 0;
    int layer = 0;

    AttributesParser attributesParser;

    public:
        int error = 0;

        Tile();

        Tile(Coord, int);

        void setDesign(int);

        void drawTDSet(Shader*); // Draw, tile dimensions set
        void draw(Shader*);
        void draw(Coord, Shader*);

        int getLayer();

        Tile* getThis();
};

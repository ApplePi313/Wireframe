#pragma once

#include <string>
#include <iostream>

#include "Shaders/Shader.hpp"
#include "AttributesParser.hpp"

/*
    Designs:
    0: floor
    1: box
*/

/* Error Codes
    1: failed file read
    2: Failed to read vertices/indices
*/

class Tile {
    int size = 64; // Tile size in pixels

    int design = 0;
    int layer = 0;

    AttributesParser attributesParser;

    public:
        int error = 0;

        Tile();

        Tile(int, Shader*);

        void setDesign(int, Shader*);

        void draw(float, float, Shader*);

        int getLayer();
};

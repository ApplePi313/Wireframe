#pragma once

#include <string>
#include <iostream>

#include "Shaders/Shader.hpp"
#include "AttributesParser.hpp"

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
    float xPos = 0.0f;
    float yPos = 0.0f;

    int size = 64; // Tile size in pixels

    int design = 0;
    int layer = 0;

    AttributesParser attributesParser;

    public:
        int error = 0;

        Tile();

        Tile(float, float, int);

        void setDesign(int);

        void drawTDSet(Shader*); // Draw, tile dimensions set
        void draw(Shader*);
        void draw(float, float, Shader*);

        int getLayer();

        Tile* getThis();
};

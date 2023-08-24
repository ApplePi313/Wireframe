#include "World/Tile.hpp"

Tile::Tile() {}

Tile::Tile(float x, float y, int tileSize, Shader* shader) {
    xPos = x;
    yPos = y;

    size = tileSize;

    setDesign(0, shader);
}

void Tile::setDesign(int tileDesign, Shader* shader) {
    design = tileDesign;

    attributesParser.readFile(((std::string) ("src/Assets/Tiles/Tile" + std::to_string(design) + ".attr")).c_str());

    (*shader).activate();
    (*shader).setVertices(attributesParser.verticesPtr, attributesParser.verticesLen, attributesParser.indicesPtr, attributesParser.indicesLen);

    switch(design) {
        case 0: 
            layer = 0;

            break;
        case 1:
            layer = 2;

            break;
        case 2:
            layer = 1;

            break;
    }
}

void Tile::draw(float x, float y, Shader* shader) {
    glLineWidth(attributesParser.strokeWidth);

    (*shader).setVertices(attributesParser.verticesPtr, attributesParser.verticesLen, attributesParser.indicesPtr, attributesParser.indicesLen);

    // std::cout << design << std::endl;

    // (*shader).set2f("worldCoords", x, y);
    (*shader).set2f("coords", xPos, yPos);
    (*shader).draw();
}

int Tile::getLayer() {
    return layer;
}

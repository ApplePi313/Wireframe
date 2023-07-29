#include "World/Tile.hpp"

Tile::Tile() {}

Tile::Tile(int tileSize, Shader* shader) {
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
            layer = 1;

            break;
    }
}

void Tile::draw(float x, float y, Shader* shader) {
    glLineWidth(attributesParser.strokeWidth);

    (*shader).setVertices(attributesParser.verticesPtr, attributesParser.verticesLen, attributesParser.indicesPtr, attributesParser.indicesLen);

    // std::cout << design << std::endl;

    (*shader).set2f("coords", x, y);

    (*shader).draw();
}

int Tile::getLayer() {
    return layer;
}

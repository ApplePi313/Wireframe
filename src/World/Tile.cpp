#include "World/Tile.hpp"

Tile::Tile() {
    setDesign(0);
}

Tile::Tile(Coord c, int tileSize) {
    coords = c;

    size = tileSize;

    setDesign(0);
}

void Tile::setDesign(int tileDesign) {
    design = tileDesign;

    attributesParser.readFile(((std::string) ("src/Assets/Tiles/Tile" + std::to_string(design) + ".attr")).c_str());


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

void Tile::drawTDSet(Shader* shader) { // Ideally the world coords and tile dimensions are already set
    glLineWidth(attributesParser.strokeWidth);

    (*shader).updateVertices(attributesParser.verticesPtr, attributesParser.verticesLen, attributesParser.indicesPtr, attributesParser.indicesLen);

    (*shader).set2f("coords", coords.x, coords.y);
    (*shader).draw();
}

void Tile::draw(Shader* shader) { // Less ideally just the world coords are already set
    glLineWidth(attributesParser.strokeWidth);

    (*shader).setVertices(attributesParser.verticesPtr, attributesParser.verticesLen, attributesParser.indicesPtr, attributesParser.indicesLen);

    // std::cout << design << std::endl;

    (*shader).set2f("dimensions", size, size);
    (*shader).set2f("resize", size/2.0f, -size/2.0f);

    (*shader).set2f("coords", coords.x, coords.y);
    (*shader).draw();
}

void Tile::draw(Coord c, Shader* shader) {
    glLineWidth(attributesParser.strokeWidth);

    (*shader).setVertices(attributesParser.verticesPtr, attributesParser.verticesLen, attributesParser.indicesPtr, attributesParser.indicesLen);

    // std::cout << design << std::endl;

    (*shader).set2f("dimensions", 64.0f, 64.0f);
    (*shader).set2f("resize", 32, -32);

    (*shader).set2f("worldCoords", c.x, c.x);
    (*shader).set2f("coords", coords.x, coords.y);
    (*shader).draw();
}

int Tile::getLayer() {
    return layer;
}

Tile* Tile::getThis() {
    return this;
}
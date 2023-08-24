#include "World/Level.hpp"


Level::Level() {}
Level::Level(float x, float y, int levelTileWidth, int levelTileHeight) {
    setup(x, y, levelTileWidth, levelTileHeight);
}

void Level::setup(float x, float y, int levelTileWidth, int levelTileHeight) {
    xPos = x;
    yPos = y;

    tileWidth = levelTileWidth;
    tileHeight = levelTileHeight;
}

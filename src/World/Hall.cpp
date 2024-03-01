#include "World/Hall.hpp"

Hall::Hall() {}

Hall::Hall(float x, float y, int hallTileWidth, int hallTileHeight, int hallOrientation, Tile** tilesPtr, Hitbox** hitboxesPtr, int tilesOffsetX, int tilesOffsetY) {
    altSetup(x, y, hallTileWidth, hallTileHeight, hallOrientation, tilesPtr, hitboxesPtr, tilesOffsetX, tilesOffsetY);
}

Hall::Hall(float x, float y, int hallTileWidth, int hallTileHeight, int hallOrientation, const char* vertexShaderFile, const char* fragmentShaderFile) {
    setup(x, y, hallTileWidth, hallTileHeight, hallOrientation, vertexShaderFile, fragmentShaderFile);
}

void Hall::altSetup(float x, float y, int hallTileWidth, int hallTileHeight, int hallOrientation, Tile** hallTilesPtr, Hitbox** hallHitboxesPtr, int tilesOffsetX, int tilesOffsetY) {
    xPos = x;
    yPos = y;

    tileWidth = hallTileWidth;
    tileHeight = hallTileHeight;

    orientation = hallOrientation;

    tilesPtr = hallTilesPtr;
    hitboxesPtr = hallHitboxesPtr;

    for (int i = tilesOffsetY; i < tileHeight + tilesOffsetY; i++) {
        for (int j = tilesOffsetX; j < tileWidth + tilesOffsetX; j++) {
            tilesPtr[i][j] = Tile(xPos + j * 64.0f, yPos + i * 64.0f, 64);
            hitboxesPtr[i][j] = Hitbox(xPos + j * 64.0f, yPos + i * 64.0f, 64.0f, 64.0f, 0);
        }
    }

    if (orientation == 0) {
        for (int i = tilesOffsetX; i < tileWidth + tilesOffsetX; i++) { // set the side walls of the room
            tilesPtr[tilesOffsetY][i].setDesign(2);
            hitboxesPtr[tilesOffsetY][i].setType(1);

            tilesPtr[tileHeight - 1 + tilesOffsetY][i].setDesign(2);
            hitboxesPtr[tileHeight - 1 + tilesOffsetY][i].setType(1);
        }
    } else if (orientation == 1) {
        for (int i = tilesOffsetY; i < tileHeight + tilesOffsetY; i++) {
            tilesPtr[i][tilesOffsetX].setDesign(2);
            hitboxesPtr[i][tilesOffsetX].setType(1);

            tilesPtr[i][tileWidth - 1 + tilesOffsetX].setDesign(2);
            hitboxesPtr[i][tileWidth - 1 + tilesOffsetX].setType(1);
        }
    } else {
        std::cout << "Invalid orientation: " << orientation << " for a hall" << std::endl;
        error = 1;
    }
}
void Hall::setup(float x, float y, int hallTileWidth, int hallTileHeight, int hallOrientation, const char* vertexShaderFile, const char* fragmentShaderFile) {
    xPos = x;
    yPos = y;

    tileWidth = hallTileWidth;
    tileHeight = hallTileHeight;

    orientation = hallOrientation;

    shader.fileSetup(vertexShaderFile, fragmentShaderFile);

    tilesPtr = new Tile*[tileHeight];
    hitboxesPtr = new Hitbox*[tileHeight];

    for (int i = 0; i < tileHeight; i++) {
        *(tilesPtr + i) = new Tile[tileWidth];
        *(hitboxesPtr + i) = new Hitbox[tileWidth];
    }

    for (int i = 0; i < tileHeight; i++) {
        for (int j = 0; j < tileWidth; j++) {
            *(*(tilesPtr + i) + j) = Tile(xPos + j * 64.0f, yPos + i * 64.0f, 64);
            *(*(hitboxesPtr + i) + j) = Hitbox(xPos + j * 64.0f, yPos + i * 64.0f, 64.0f, 64.0f, 0);
        }
    }

    if (orientation == 0) {
        for (int i = 0; i < tileWidth; i++) { // set the side walls of the room
            (*(*(tilesPtr + 0) + i)).setDesign(2);
            (*(*(hitboxesPtr + 0) + i)).setType(1);

            (*(*(tilesPtr + tileHeight - 1) + i)).setDesign(2);
            (*(*(hitboxesPtr + tileHeight - 1) + i)).setType(1);
        }
    } else if (orientation == 1) {
        for (int i = 0; i < tileHeight; i++) {
            (*(*(tilesPtr + i) + 0)).setDesign(2);
            (*(*(hitboxesPtr + i) + 0)).setType(1);

            (*(*(tilesPtr + i) + tileWidth - 1)).setDesign(2);
            (*(*(hitboxesPtr + i) + tileWidth - 1)).setType(1);
        }
    } else {
        std::cout << "Invalid orientation: " << orientation << " for a hall" << std::endl;
        error = 1;
    }
}

void Hall::draw(float x, float y) {
    activateShader();

    shader.set2f("dimensions", 64.0f, 64.0f);
    shader.set2f("resize", 32, -32);
    shader.set2f("worldCoords", x, y);

    for (int layer = 0; layer < 10; layer++) {
        for (int i = 0; i < tileHeight; i++) {
            for (int j = 0; j < tileWidth; j++) {
                if ((*(*(tilesPtr + i) + j)).getLayer() == layer) (*(*(tilesPtr + i) + j)).draw(x, y, &shader);
            }
        }
    }
}

void Hall::getHitboxes(Hitbox*** outHitboxesPtr, int* outWidth, int* outHeight) {
    *outHitboxesPtr = hitboxesPtr;
    *outWidth = tileWidth;
    *outHeight = tileHeight;
}

void Hall::close() {
    for (int i = 0; i < tileHeight; i++) {
        delete[] *(tilesPtr + i);
        delete[] *(hitboxesPtr + i);
    }

    delete[] tilesPtr;
    delete[] hitboxesPtr;

    return;
}

void Hall::activateShader() {
    shader.activate();
}

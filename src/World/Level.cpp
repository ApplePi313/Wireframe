#include "World/Level.hpp"


Level::Level() {}
Level::Level(float x, float y, int levelTileWidth, int levelTileHeight, const char* inVertexShaderFile, const char* inFragmentShaderFile) {
    setup(x, y, levelTileWidth, levelTileHeight, inVertexShaderFile, inFragmentShaderFile);
}

void Level::setup(float x, float y, int levelTileWidth, int levelTileHeight, const char* inVertexShaderFile, const char* inFragmentShaderFile) {
    xPos = x;
    yPos = y;

    tileWidth = levelTileWidth;
    tileHeight = levelTileHeight;

    vertexShaderFile = inVertexShaderFile;
    fragmentShaderFile = inFragmentShaderFile;

    shader.fileSetup(vertexShaderFile, fragmentShaderFile);

    generate();
}

/*
 * Precondition: tileWidth and tileHeight are greater than or equal to 20
 */

void Level::generate() {
    if (mini(tileWidth, tileHeight) / 20 < 0) {
        std::cout << " This Level is too small! (not generating it)" << std::endl;
        return;
    }
    // Initialize the tiles and hitboxes
    tilesPtr = new Tile*[tileHeight];
    hitboxesPtr = new Hitbox*[tileHeight];

    for (int i = 0; i < tileHeight; i++) {
        tilesPtr[i] = new Tile[tileWidth];
        hitboxesPtr[i] = new Hitbox[tileWidth];
    }

    numHorizontalRooms = tileWidth / 20;
    numVerticalRooms = tileHeight / 20;

    std::cout << "num rooms: H" << numHorizontalRooms << " V" << numVerticalRooms << std::endl;

    roomsPtr = new Room*[numVerticalRooms];
    for (int i = 0; i < numVerticalRooms; i++) {
        roomsPtr[i] = new Room[numHorizontalRooms];
    }

    for (int i = 0; i < numVerticalRooms; i++) {
        for (int j = 0; j < numHorizontalRooms; j++) {
            rbcWidth = randGen.getPositiveInt() % 10 + 10;
            rbcHeight = randGen.getPositiveInt() % 10 + 10;

            roomsPtr[i][j] = Room(xPos + 64 * 20 * j, yPos + 64 * 20 * i, rbcWidth, rbcHeight, 0, tilesPtr, hitboxesPtr, 20 * j, 20 * i);
        }
    }

    // Now generate the halls
    for (int i = 0; i < numVerticalRooms; i++) {
        for (int j = 0; j < numHorizontalRooms; j++) {
            if (i + 1 < numVerticalRooms) {
                hallPos = randGen.getPositiveInt() % 
                          (mini(roomsPtr[i][j].getWidth(), roomsPtr[i+1][j].getWidth()) - 4);

                if (randGen.chance(50)) {
                    Hall* tmpHall = new Hall(xPos, yPos, // just pass in the level's coords here, the tile offsets will do the rest
                                             4, 20 - roomsPtr[i][j].getHeight() + 2, 1, 
                                             tilesPtr, hitboxesPtr, 20 * j + hallPos, 20 * i + roomsPtr[i][j].getHeight() - 1);
                    delete tmpHall;
                }
            }


            if (j + 1 < numHorizontalRooms) {
                hallPos = randGen.getPositiveInt() % 
                          (mini(roomsPtr[i][j].getHeight(), roomsPtr[i][j+1].getHeight()) - 4);

                if (randGen.chance(50)) {
                    Hall* tmpHall = new Hall(xPos, yPos, // just pass in the level's coords here, the tile offsets will do the rest
                                             20 - roomsPtr[i][j].getWidth() + 2, 4, 0, 
                                             tilesPtr, hitboxesPtr, 20 * j + roomsPtr[i][j].getWidth() - 1, 20 * i + hallPos);
                    delete tmpHall;
                }
            }
        }
    }


    for (int i = 0; i < numVerticalRooms; i++) {
        delete[] roomsPtr[i];
    }
    delete[] roomsPtr;
}

void Level::draw(float worldX, float worldY) {
    shader.activate();

    shader.set2f("dimensions", 64.0f, 64.0f);
    shader.set2f("resize", 32, -32);
    shader.set2f("worldCoords", worldX, worldY);

    for (int layer = 0; layer < 10; layer++) {
        for (int i = 0; i < tileHeight; i++) {
            for (int j = 0; j < tileWidth; j++) {
                if (tilesPtr[i][j].getLayer() == layer) tilesPtr[i][j].drawTDSet(&shader);
            }
        }
    }
}

void Level::getHitboxes(Hitbox*** outHitboxesPtr, int* outWidth, int* outHeight) {
    *outHitboxesPtr = hitboxesPtr;
    *outWidth = tileWidth;
    *outHeight = tileHeight;
}
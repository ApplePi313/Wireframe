#include "World/Level.hpp"


Level::Level() {}
Level::Level(Coord c, int levelTileWidth, int levelTileHeight, const char* inVertexShaderFile, const char* inFragmentShaderFile) {
    setup(c, levelTileWidth, levelTileHeight, inVertexShaderFile, inFragmentShaderFile);
}

void Level::setup(Coord c, int levelTileWidth, int levelTileHeight, const char* inVertexShaderFile, const char* inFragmentShaderFile) {
    coords = c;

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

            roomsPtr[i][j] = Room(coords + Coord(64 * 20 * j, 64 * 20 * i), rbcWidth, rbcHeight, 0, tilesPtr, hitboxesPtr, 20 * j, 20 * i);
        }
    }

    // Now generate the halls
    for (int i = 0; i < numVerticalRooms; i++) {
        for (int j = 0; j < numHorizontalRooms; j++) {
            if (i + 1 < numVerticalRooms) {
                hallPos = randGen.getPositiveInt() % 
                          (mini(roomsPtr[i][j].getWidth(), roomsPtr[i+1][j].getWidth()) - 4);

                if (randGen.chance(50)) {
                    Hall* tmpHall = new Hall(coords, // just pass in the level's coords here, the tile offsets will do the rest
                                             4, 20 - roomsPtr[i][j].getHeight() + 2, 1, 
                                             tilesPtr, hitboxesPtr, 20 * j + hallPos, 20 * i + roomsPtr[i][j].getHeight() - 1);
                    delete tmpHall;
                }
            }


            if (j + 1 < numHorizontalRooms) {
                hallPos = randGen.getPositiveInt() % 
                          (mini(roomsPtr[i][j].getHeight(), roomsPtr[i][j+1].getHeight()) - 4);

                if (randGen.chance(50)) {
                    Hall* tmpHall = new Hall(coords, // just pass in the level's coords here, the tile offsets will do the rest
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

void Level::draw(Coord c) {
    shader.activate();

    shader.set2f("dimensions", 64.0f, 64.0f);
    shader.set2f("resize", 32, -32);
    shader.set2f("worldCoords", c.x, c.y);

    for (int layer = 0; layer < 10; layer++) {
        for (int i = 0; i < tileHeight; i++) {
            for (int j = 0; j < tileWidth; j++) {
                if (tilesPtr[i][j].getLayer() == layer) tilesPtr[i][j].drawTDSet(&shader);
            }
        }
    }

    character.draw(c);
}

void Level::setCharacter(Character newCharacter) {
    character = newCharacter;
}

void Level::setCoords(Coord c) {
    coords = c;
}

void Level::getHitboxes(Hitbox*** outHitboxesPtr, int* outWidth, int* outHeight) {
    *outHitboxesPtr = hitboxesPtr;
    *outWidth = tileWidth;
    *outHeight = tileHeight;
}

void Level::moveCharacter(int* xChange, int* yChange) {
    // if the character is outside of the level, don't block movement
    if (character.getCoords().x < coords.x || character.getCoords().x > coords.x + tileWidth * 64 ||
        character.getCoords().y < coords.y || character.getCoords().y > coords.y + tileHeight * 64) {

        std::cout << "character out of level bounds\n";

        character.translate(Coord(*xChange, *yChange));
        return;
    }

    Hitbox tmpHitbox = character.getHitbox();

    if (*xChange > 0) {
        for (int i = 0; i < *xChange; i++) {
            tmpHitbox.translate(Coord(1, 0));
            
            for (int j = 0; j <= ((tmpHitbox.getY()%64 + tmpHitbox.getHeight()) / 64); j++) {
                for (int k = 0; k <= ((tmpHitbox.getX()%64 + tmpHitbox.getWidth()) / 64); k++) {
                    if (hitboxesPtr[j + (tmpHitbox.getY() - coords.y)/64][k + (tmpHitbox.getX() - coords.x)/64].isBlocking() && 
                        !hitboxesPtr[j + (tmpHitbox.getY() - coords.y)/64][k + (tmpHitbox.getX() - coords.x)/64]
                            .isColliding(character.getHitbox())) {

                        tmpHitbox.translate(Coord(-1, 0));
                    }
                }
            }
        }
    } else {
        for (int i = 0; i > *xChange; i--) {
            tmpHitbox.translate(Coord(-1, 0));
            
            for (int j = 0; j <= ((tmpHitbox.getY()%64 + tmpHitbox.getHeight()) / 64); j++) {
                for (int k = 0; k <= ((tmpHitbox.getX()%64 + tmpHitbox.getWidth()) / 64); k++) {
                    if (hitboxesPtr[j + (tmpHitbox.getY() - coords.y)/64][k + (tmpHitbox.getX() - coords.x)/64].isBlocking() && 
                        !hitboxesPtr[j + (tmpHitbox.getY() - coords.y)/64][k + (tmpHitbox.getX() - coords.x)/64]
                            .isColliding(character.getHitbox())) {

                        tmpHitbox.translate(Coord(1, 0));
                    }
                }
            }
        }
    }

    if (*yChange > 0) {
        for (int i = 0; i < *yChange; i++) {
            tmpHitbox.translate(Coord(0, 1));
            
            for (int j = 0; j <= ((tmpHitbox.getY()%64 + tmpHitbox.getHeight()) / 64); j++) {
                for (int k = 0; k <= ((tmpHitbox.getX()%64 + tmpHitbox.getWidth()) / 64); k++) {
                    if (hitboxesPtr[j + (tmpHitbox.getY() - coords.y)/64][k + (tmpHitbox.getX() - coords.x)/64].isBlocking() && 
                        !hitboxesPtr[j + (tmpHitbox.getY() - coords.y)/64][k + (tmpHitbox.getX() - coords.x)/64]
                            .isColliding(character.getHitbox())) {

                        tmpHitbox.translate(Coord(0, -1));
                    }
                }
            }
        }
    } else {
        for (int i = 0; i > *yChange; i--) {
            tmpHitbox.translate(Coord(0, -1));
            
            for (int j = 0; j <= ((tmpHitbox.getY()%64 + tmpHitbox.getHeight()) / 64); j++) {
                for (int k = 0; k <= ((tmpHitbox.getX()%64 + tmpHitbox.getWidth()) / 64); k++) {
                    if (hitboxesPtr[j + (tmpHitbox.getY() - coords.y)/64][k + (tmpHitbox.getX() - coords.x)/64].isBlocking() && 
                        !hitboxesPtr[j + (tmpHitbox.getY() - coords.y)/64][k + (tmpHitbox.getX() - coords.x)/64]
                            .isColliding(character.getHitbox())) {

                        tmpHitbox.translate(Coord(0, 1));
                    }
                }
            }
        }
    }


    *xChange = (tmpHitbox.getCoords() - character.getCoords()).x;
    *yChange = (tmpHitbox.getCoords() - character.getCoords()).y;
    character.translate(Coord(*xChange, *yChange));
}
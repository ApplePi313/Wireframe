#include <iostream>

#include "World/Room.hpp"

Room::Room() {}

Room::Room(float x, float y, int roomWidth, int roomHeight, int roomDesign, const char* vertexShaderFile, const char* fragmentShaderFile) {
    setup(x, y, roomWidth, roomHeight, roomDesign, vertexShaderFile, fragmentShaderFile);
}

void Room::setup(float x, float y, int roomWidth, int roomHeight, int roomDesign, const char* vertexShaderFile, const char* fragmentShaderFile) {
    xPos = x;
    yPos = y;

    width = roomWidth;
    height = roomHeight;

    usableWidth = width - 2; // this accounts for the 1-thick walls
    usableHeight = height - 2; 

    design = roomDesign;

    shader.fileSetup(vertexShaderFile, fragmentShaderFile);

    tilesPtr = new Tile*[height];
    hitboxesPtr = new Hitbox*[height];

    for (int i = 0; i < height; i++) {
        *(tilesPtr + i) = new Tile[height];
        *(hitboxesPtr + i) = new Hitbox[height];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            *(*(tilesPtr + i) + j) = Tile(xPos + j * 64.0f, yPos + i * 64.0f, 64, &shader);
            *(*(hitboxesPtr + i) + j) = Hitbox(xPos + j * 64.0f, yPos + i * 64.0f, 64.0f, 64.0f, 0);
        }
    }

    for (int i = 0; i < width; i++) { // set the side walls of the room
        (*(*(tilesPtr + 0) + i)).setDesign(2, &shader);
        (*(*(hitboxesPtr + 0) + i)).setType(1);

        (*(*(tilesPtr + height - 1) + i)).setDesign(2, &shader);
        (*(*(hitboxesPtr + height - 1) + i)).setType(1);
    }
    for (int i = 0; i < height - 2; i++) {
        (*(*(tilesPtr + i + 1) + 0)).setDesign(2, &shader);
        (*(*(hitboxesPtr + i + 1) + 0)).setType(1);

        (*(*(tilesPtr + i + 1) + width - 1)).setDesign(2, &shader);
        (*(*(hitboxesPtr + i + 1) + width - 1)).setType(1);
    }

    generate();
}

void Room::generate() {
    
    std::cout << "rand test: " << randGen.getPositiveInt() << std::endl;

    switch (design) {
        case 0: 
            numBoxes = (randGen.getPositiveInt()) % 10 + 3; // min 3 max 12 boxes

        break;
    }

    boxesXPtr = new int[numBoxes];
    boxesYPtr = new int[numBoxes];

    do {
        for (int i = 0; i < numBoxes; i++) {
            *(boxesXPtr + i) = randGen.getPositiveInt() % usableWidth + 1;
            *(boxesYPtr + i) = randGen.getPositiveInt() % usableHeight + 1;
        }

        boxesAreSeparate = true;

        for (int i = 0; i < numBoxes; i++) {
            for (int j = 0; j < numBoxes; j++) {
                if (i == j) continue;


                if (*(boxesXPtr + i) == *(boxesXPtr + j) &&
                    *(boxesYPtr + i) == *(boxesYPtr + j)) {
                        
                    boxesAreSeparate = false;
                }
            }
        }
    } while (!boxesAreSeparate);

    for (int i = 0; i < numBoxes; i++) {
        (*(*(tilesPtr + *(boxesYPtr + i)) + *(boxesXPtr + i))).setDesign(1, &shader);
        (*(*(hitboxesPtr + *(boxesYPtr + i)) + *(boxesXPtr + i))).setType(1);
    }

    return;
}

void Room::activateShader() {
    shader.activate();
}

void Room::draw(float x, float y) {
    activateShader();

    shader.set2f("dimensions", 64.0f, 64.0f);
    shader.set2f("resize", 32, -32);
    shader.set2f("screenDimensions", 800, 600);

    shader.set2f("worldCoords", x, y);

    for (int layer = 0; layer < 10; layer++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if ((*(*(tilesPtr + i) + j)).getLayer() == layer) (*(*(tilesPtr + i) + j)).draw(x, y, &shader);
            }
        }
    }
}

void Room::getHitboxes(Hitbox*** outHitboxesPtr, int* outWidth, int* outHeight) {
    *outHitboxesPtr = hitboxesPtr;
    *outWidth = width;
    *outHeight = height;
}

void Room::close() {
    for (int i = 0; i < height; i++) {
        delete[] *(tilesPtr + i);
        delete[] *(hitboxesPtr + i);
    }

    delete[] tilesPtr;
    delete[] hitboxesPtr;

    return;
}

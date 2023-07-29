#include <iostream>

#include "World/Room.hpp"

Room::Room() {}

Room::Room(int roomWidth, int roomHeight, int roomDesign, const char* vertexShaderFile, const char* fragmentShaderFile) {
    setup(roomWidth, roomHeight, roomDesign, vertexShaderFile, fragmentShaderFile);
}

void Room::setup(int roomWidth, int roomHeight, int roomDesign, const char* vertexShaderFile, const char* fragmentShaderFile) {
    width = roomWidth;
    height = roomHeight;

    usableWidth = width - 2; // this accounts for the 1-thick walls
    usableHeight = height - 2; 

    design = roomDesign;

    shader.fileSetup(vertexShaderFile, fragmentShaderFile);

    tilesPtr = new Tile*[width];

    for (int i = 0; i < height; i++) {
        *(tilesPtr + i) = new Tile[height];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            *(*(tilesPtr + j) + i) = Tile(64, &shader);
        }
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
            *(boxesXPtr + i) = randGen.getPositiveInt() % usableWidth;
            *(boxesYPtr + i) = randGen.getPositiveInt() % usableHeight;
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
    }

    return;
}

void Room::activateShader() {
    shader.activate();
}

void Room::draw(float x, float y) {
    activateShader();

    shader.set2f("resize", 32, -32);
    shader.set2f("screenDimensions", 800, 600);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((*(*(tilesPtr + j) + i)).getLayer() == 0) (*(*(tilesPtr + j) + i)).draw(64 * j + x, 64 * i + y, &shader);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ((*(*(tilesPtr + j) + i)).getLayer() == 1) (*(*(tilesPtr + j) + i)).draw(64 * j + x, 64 * i + y, &shader);
        }
    }
}

void Room::close() {
    for (int i = 0; i < height; i++) {
        delete[] *(tilesPtr + i);
    }

    delete[] tilesPtr;

    return;
}

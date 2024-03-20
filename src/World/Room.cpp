#include "World/Room.hpp"

Room::Room() {}

Room::Room(Coord c, int roomWidth, int roomHeight, int roomDesign, const char* vertexShaderFile, const char* fragmentShaderFile) {
    setup(c, roomWidth, roomHeight, roomDesign, vertexShaderFile, fragmentShaderFile);
}
Room::Room(Coord c, int roomWidth, int roomHeight, int roomDesign, Tile** tilesPtr, Hitbox** hitboxesPtr, int tilesOffsetX, int tilesOffsetY) {
    setup(c, roomWidth, roomHeight, roomDesign, tilesPtr, hitboxesPtr, tilesOffsetX, tilesOffsetY);
}

void Room::setup(Coord c, int roomWidth, int roomHeight, int roomDesign, const char* vertexShaderFile, const char* fragmentShaderFile) {
    coords = c;

    width = roomWidth;
    height = roomHeight;

    usableWidth = width - 2; // this accounts for the 1-thick walls
    usableHeight = height - 2;

    design = roomDesign;

    shader.fileSetup(vertexShaderFile, fragmentShaderFile);

    tilesPtr = new Tile*[height];
    hitboxesPtr = new Hitbox*[height];

    for (int i = 0; i < height; i++) { // inner layer(1 pointer level) is height
        tilesPtr[i] = new Tile[width]; // outer layer(0 pointer levels) is width
        hitboxesPtr[i] = new Hitbox[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tilesPtr[i][j] = Tile(c + Coord(j * 64.0f, i * 64.0f), 64);
            hitboxesPtr[i][j] = Hitbox(c + Coord(j * 64.0f, i * 64.0f), 64.0f, 64.0f, 0);
        }
    }

    for (int i = 0; i < width; i++) { // set the side walls of the room
        tilesPtr[0][i].setDesign(2);
        hitboxesPtr[0][i].setType(1);

        tilesPtr[height-1][i].setDesign(2);
        hitboxesPtr[height-1][i].setType(1);
    }
    for (int i = 0; i < height - 2; i++) {
        tilesPtr[i+1][0].setDesign(2);
        hitboxesPtr[i+1][0].setType(1);

        tilesPtr[i+1][width-1].setDesign(2);
        hitboxesPtr[i+1][width-1].setType(1);
    }

    generate(0, 0);
}
void Room::setup(Coord c, int roomWidth, int roomHeight, int roomDesign, Tile** roomTilesPtr, Hitbox** roomHitboxesPtr, int tilesOffsetX, int tilesOffsetY) {
    coords = c;

    width = roomWidth;
    height = roomHeight;

    usableWidth = width - 2; // this accounts for the 1-thick walls
    usableHeight = height - 2;

    design = roomDesign;

    tilesPtr = roomTilesPtr;
    hitboxesPtr = roomHitboxesPtr;

    // for (int i = 0; i < height; i++) { // inner layer(1 pointer level) is height
    //     *(tilesPtr + i + tilesOffsetY) = new Tile[width]; // outer layer(0 pointer levels) is width
    //     *(hitboxesPtr + i + tilesOffsetY) = new Hitbox[width];
    // }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tilesPtr[i+tilesOffsetY][j+tilesOffsetX] = Tile(c + Coord(j * 64.0f, i * 64.0f), 64);
            hitboxesPtr[i+tilesOffsetY][j+tilesOffsetX] = Hitbox(c + Coord(j * 64.0f, i * 64.0f), 64.0f, 64.0f, 0);
        }
    }

    for (int i = 0; i < width; i++) { // set the side walls of the room
        tilesPtr[tilesOffsetY][i+tilesOffsetX].setDesign(2);
        hitboxesPtr[tilesOffsetY][i+tilesOffsetX].setType(1);

        tilesPtr[height-1+tilesOffsetY][i+tilesOffsetX].setDesign(2);
        hitboxesPtr[height-1+tilesOffsetY][i+tilesOffsetX].setType(1);
    }
    for (int i = 0; i < height - 2; i++) {
        tilesPtr[i+1+tilesOffsetY][tilesOffsetX].setDesign(2);
        hitboxesPtr[i+1+tilesOffsetY][tilesOffsetX].setType(1);

        tilesPtr[i+1+tilesOffsetY][width-1+tilesOffsetX].setDesign(2);
        hitboxesPtr[i+1+tilesOffsetY][width-1+tilesOffsetX].setType(1);
    }

    generate(tilesOffsetX, tilesOffsetY);
}

void Room::generate(int tilesOffsetX, int tilesOffsetY) {
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
        (*(*(tilesPtr + *(boxesYPtr + i) + tilesOffsetY) + *(boxesXPtr + i) + tilesOffsetX)).setDesign(1);
        (*(*(hitboxesPtr + *(boxesYPtr + i) + tilesOffsetY) + *(boxesXPtr + i) + tilesOffsetX)).setType(1);
    }

    delete[] boxesXPtr;
    delete[] boxesYPtr;    

    return;
}


/*
* Create a gateway at a specified location with a specified height
* side begins with 0 at the top, then goes clockwise, to 3 on the left
* position indicates how far from the top or left(depending on the side) the gate will form
* width is the size of the gate. Must be at least 1
*/
int Room::formEntry(int entrySide, int entryPosition, int entryWidth) { 
    if (entryWidth <= 0) {
        std::cout << "Attempted to create gate of width: " << entryWidth << std::endl;
        return -1;
    }
    
    switch(entrySide) {
        case 0:
            for(int i = 0; i < entryWidth; i++) {
                tilesPtr[0][entryPosition + i].setDesign(0);
                hitboxesPtr[0][entryPosition + i].setType(0);
            }
            break;

        case 1:
            for (int i = 0; i < entryWidth; i++) {
                tilesPtr[entryPosition + i][width].setDesign(0);
                hitboxesPtr[entryPosition + i][width].setType(0);
            }
            break;

        case 2:
            for(int i = 0; i < entryWidth; i++) {
                tilesPtr[height][entryPosition + i].setDesign(0);
                hitboxesPtr[height][entryPosition + i].setType(0);
            }
            break;

        case 3:
            for (int i = 0; i < entryWidth; i++) {
                tilesPtr[entryPosition + i][0].setDesign(0);
                hitboxesPtr[entryPosition + i][0].setType(0);
            }
            break;

        default:
            std::cout << "Attempted to create gateway on invalid side: " << entrySide << std::endl;
            break;
    }

    return 0;
}

int Room::formEntry(int entrySide, int entryPosition, int entryWidth, Tile** tilesPtr, Hitbox** hitboxesPtr, int tilesOffsetX, int tilesOffsetY) { 
    if (entryWidth <= 0) {
        std::cout << "Attempted to create gate of width: " << entryWidth << std::endl;
        return -1;
    }
    
    switch(entrySide) {
        case 0:
            for(int i = 0; i < entryWidth; i++) {
                tilesPtr[0 + tilesOffsetY][entryPosition + i + tilesOffsetX].setDesign(0);
                hitboxesPtr[0 + tilesOffsetY][entryPosition + i + tilesOffsetX].setType(0);
            }
            break;

        case 1:
            for (int i = 0; i < entryWidth; i++) {
                tilesPtr[entryPosition + i + tilesOffsetY][width + tilesOffsetX].setDesign(0);
                hitboxesPtr[entryPosition + i + tilesOffsetY][width + tilesOffsetX].setType(0);
            }
            break;

        case 2:
            for(int i = 0; i < entryWidth; i++) {
                tilesPtr[height + tilesOffsetY][entryPosition + i + tilesOffsetX].setDesign(0);
                hitboxesPtr[height + tilesOffsetY][entryPosition + i + tilesOffsetX].setType(0);
            }
            break;

        case 3:
            for (int i = 0; i < entryWidth; i++) {
                tilesPtr[entryPosition + i + tilesOffsetY][0 + tilesOffsetX].setDesign(0);
                hitboxesPtr[entryPosition + i + tilesOffsetY][0 + tilesOffsetX].setType(0);
            }
            break;

        default:
            std::cout << "Attempted to create gateway on invalid side: " << entrySide << std::endl;
            break;
    }

    return 0;
}

void Room::activateShader() {
    shader.activate();
}

void Room::draw(Coord c) {
    activateShader();

    shader.set2f("dimensions", 64.0f, 64.0f);
    shader.set2f("resize", 32, -32);
    shader.set2f("worldCoords", c.x, c.y);

    for (int layer = 0; layer < 10; layer++) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (tilesPtr[i][j].getLayer() == layer) tilesPtr[i][j].drawTDSet(&shader);
            }
        }
    }
}

void Room::getHitboxes(Hitbox*** outHitboxesPtr, int* outWidth, int* outHeight) {
    *outHitboxesPtr = hitboxesPtr;
    *outWidth = width;
    *outHeight = height;
}

void Room::getTiles(Tile*** outTilesPtr, int* outWidth, int* outHeight) {
    *outTilesPtr = tilesPtr;
    *outWidth = width;
    *outHeight = height;
}

int Room::getWidth() {
    return width;
}
int Room::getHeight() {
    return height;
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

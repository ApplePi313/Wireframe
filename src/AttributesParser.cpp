#include "AttributesParser.hpp"

AttributesParser::AttributesParser() {}

AttributesParser::AttributesParser(const char* inFile) {
    readFile(inFile);
}

void AttributesParser::readFile(const char* inFile) {
    fInStrm.open(inFile, std::ios_base::in);

    if (!fInStrm.is_open()) {

        std::cout << "Failed to open file: " << inFile << std::endl;

        error = 1;
    }

    parseAttributes();

    parseVertices();
    parseIndices();

    for (int i = 0; i < attributesLen; i++) {
        switch (*(attributesPtr + i)) {
            case 0:
                parseStroke();

                break;
            case 1:
                parseBulletSpawns();

                break;
        }
    }

    fInStrm.close();
}

void AttributesParser::parseAttributes() {
           /*

            Attributes Parsing

            */

    fInStrm.seekg(0);

    while(fInStrm.get(extractedChar)) { // find start of attributes
        if (extractedChar == 'a') {
            break;
        }
    }

    attributesStart = fInStrm.tellg();

    attributesLen = 0;

    while(fInStrm.get(extractedChar)) { // find end and determine the length

        if (extractedChar == 'e') {
            attributesLen++; // adds one to the vertex count because there isn't a comma after the last one
            break;
        }

        if (extractedChar == ',') { // counts the number of attributes
            attributesLen++;
        }
    }

    // Start parsing attributes
    fInStrm.seekg(attributesStart);

    int attributes[attributesLen];

    for (int i = 0; i < attributesLen; i++) {
        attributes[i] = 1.0f;
    }

    currIndex = 0;

    attribute.clear();

    while (currIndex != attributesLen) {

        if (fInStrm.good()) {
            fInStrm.get(extractedChar);

        } else {
            error = 2;

            std::cout << "Ran out of characters to read when parsing attributes file(how does this happen)" << std::endl;

            break;
        }

        if (extractedChar == ',' || extractedChar == 'e') {
            attribute += "";

            attributes[currIndex] = std::stoi(attribute);

            attribute.clear();

            currIndex++;

        } else if (extractedChar == '\n' || extractedChar == ' ') {
            continue;

        } else {
            attribute += extractedChar;

        }
    }

    attributesPtr = new unsigned int[attributesLen];
    for (int i = 0; i < attributesLen; i++) {
        *(attributesPtr + i) = *(attributes + i);
    }
}

void AttributesParser::parseVertices() {
            /*

            Vertices Parsing

            */

    fInStrm.seekg(0);
    while(fInStrm.get(extractedChar)) { // find start of vertices
        if (extractedChar == 'v') {
            break;
        }
    }

    verticesStart = fInStrm.tellg();
    verticesLen = 0;

    while(fInStrm.get(extractedChar)) { // find end and determine the length

        if (extractedChar == 'e') {
            verticesLen++; // adds one to the vertex count because there isn't a comma after the last one
            break;
        }

        if (extractedChar == ',') { // counts the number of vertices
            verticesLen++;
        }
    }

    // Start parsing vertices
    fInStrm.seekg(verticesStart);

    float vertices[verticesLen];

    for (int i = 0; i < verticesLen; i++) {
        vertices[i] = 1.0f;
    }

    currIndex = 0;

    vertice.clear();

    while (currIndex != verticesLen) {

        if (fInStrm.get(extractedChar)) {
            if (extractedChar == ',' || extractedChar == 'e') {
            vertice += "";

            vertices[currIndex] = std::stof(vertice);

            vertice.clear();

            currIndex++;

        } else if (extractedChar == '\n' || extractedChar == ' ' || extractedChar == 'f') {
            continue;

        } else {
            vertice += extractedChar;

        }

        } else {
            error = 2;

            std::cout << "Failed to read character when parsing vertices file(probably ran out of characters, how does this happen)" << std::endl;

            break;
        }
    }


    verticesPtr = new float[verticesLen];
    for (int i = 0; i < verticesLen; i++) {
        *(verticesPtr + i) = *(vertices + i);
    }
}

void AttributesParser::parseIndices() {
            /*

            Indices Parsing

            */

    fInStrm.seekg(0);

    while(fInStrm.get(extractedChar)) { // find start of indices
        if (extractedChar == 'i') {
            break;
        }
    }

    indicesStart = fInStrm.tellg();

    indicesLen = 0;

    while(fInStrm.get(extractedChar)) { // find end and determine the length

        if (extractedChar == 'e') {
            indicesLen++; // adds one to the vertex count because there isn't a comma after the last one
            break;
        }

        if (extractedChar == ',') { // counts the number of indices
            indicesLen++;
        }
    }

    // Start parsing indices
    fInStrm.seekg(indicesStart);

    int indices[indicesLen];

    for (int i = 0; i < indicesLen; i++) {
        indices[i] = 1.0f;
    }

    currIndex = 0;

    indice.clear();

    while (currIndex != indicesLen) {

        if (fInStrm.good()) {
            fInStrm.get(extractedChar);

        } else {
            error = 2;

            std::cout << "Ran out of characters to read when parsing indices file(how does this happen)" << std::endl;

            break;
        }

        if (extractedChar == ',' || extractedChar == 'e') {
            indice += "";

            indices[currIndex] = std::stoi(indice);

            indice.clear();

            currIndex++;

        } else if (extractedChar == '\n' || extractedChar == ' ') {
            continue;

        } else {
            indice += extractedChar;

        }
    }

    indicesPtr = new unsigned int[indicesLen];
    for (int i = 0; i < indicesLen; i++) {
        *(indicesPtr + i) = *(indices + i);
    }
}

void AttributesParser::parseStroke() {
            /*

            Stroke Parsing

            */

    fInStrm.seekg(0);

    while(fInStrm.get(extractedChar)) { // find start of stroke
        if (extractedChar == 's') {
            break;
        }
    }

    strokeStart = fInStrm.tellg();

    while(fInStrm.get(extractedChar)) { // find end and determine the length
        if (extractedChar == 'e') {
            break;
        }
    }

    // Start parsing stroke
    fInStrm.seekg(strokeStart);

    vertice.clear();

    currIndex = 0;

    while (currIndex == 0) {
        if (fInStrm.get(extractedChar)) {
            if (extractedChar == ',' || extractedChar == 'e') {
            vertice += "";

            strokeWidth = std::stof(vertice);

            vertice.clear();

            currIndex = 1;

            } else if (extractedChar == '\n' || extractedChar == ' ' || extractedChar == 'f') {
                continue;

            } else {
                vertice += extractedChar;

            }

        } else {
            error = 2;

            std::cout << "Failed to read character when parsing stroke file(probably ran out of characters, how does this happen)" << std::endl;

            break;
        }
    }
}

void AttributesParser::parseBulletSpawns() {
            /*

            Bullet Spawn Parsing

            */

    fInStrm.seekg(0);

    while(fInStrm.get(extractedChar)) { // find start of vertices
        if (extractedChar == 'b') {
            break;
        }
    }

    bulletSpawnsStart = fInStrm.tellg();

    bulletSpawnsLen = 0;

    while(fInStrm.get(extractedChar)) { // find end and determine the length

        if (extractedChar == 'e') {
            bulletSpawnsLen++; // adds one to the vertex count because there isn't a comma after the last one
            break;
        }

        if (extractedChar == ',') { // counts the number of vertices
            bulletSpawnsLen++;
        }
    }

    // Start parsing vertices
    fInStrm.seekg(bulletSpawnsStart);

    if (bulletSpawnsLen % 2 != 0) {
        std::cout << "Invalid number of bullet spawn vertices(you have an odd amount)" << std::endl;

        error = 3;
    } else {
        numBulletSpawns = bulletSpawnsLen / 2;
    }

    float bulletSpawns[bulletSpawnsLen];

    for (int i = 0; i < bulletSpawnsLen; i++) {
        bulletSpawns[i] = 1.0f;
    }

    currIndex = 0;

    bulletSpawn.clear();

    while (currIndex != bulletSpawnsLen) {

        if (fInStrm.get(extractedChar)) {
            if (extractedChar == ',' || extractedChar == 'e') {
            bulletSpawn += "";

            bulletSpawns[currIndex] = std::stof(bulletSpawn);

            bulletSpawn.clear();

            currIndex++;

        } else if (extractedChar == '\n' || extractedChar == ' ' || extractedChar == 'f') {
            continue;

        } else {
            bulletSpawn += extractedChar;

        }

        } else {
            error = 2;

            std::cout << "Failed to read character when parsing vertices file(probably ran out of characters, how does this happen)" << std::endl;

            break;
        }
    }


    bulletSpawnsPtr = new float[bulletSpawnsLen];
    for (int i = 0; i < bulletSpawnsLen; i++) {
        *(bulletSpawnsPtr + i) = *(bulletSpawns + i);
    }
}

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

/* Error Codes
    0: fine
    1: failed file read
    2: Failed to read vertices/indices
    3: invalid setup of the attribute file
*/

/*
 * Attribute Codes:
 *  0: parse stroke width
 *  1: parse bullet spawns
 */

class AttributesParser {


    std::fstream fInStrm;
    int fileLength = 0;
    char extractedChar = 0;
    char* extractedChars;
    int currIndex = 0;

    int attributesStart = 0;
    int verticesStart = 0;
    int indicesStart = 0;
    int strokeStart = 0;
    int bulletSpawnsStart = 0;
    int bulletVerticesStart = 0;
    int bulletIndicesStart = 0;

    std::string vertex;
    std::string index;
    std::string stroke;
    std::string bulletSpawn;
    std::string attribute;
    std::string bulletVertex;
    std::string bulletIndex;


    void parseAttributes();
    void parseVertices();
    void parseIndices();
    void parseStroke();
    void parseBulletSpawns();
    void parseBulletVertices();
    void parseBulletIndices();

    public:
        int error = 0;

        int numBulletSpawns = 0;

        float* verticesPtr;
        unsigned int* indicesPtr;
        float strokeWidth = 5.0f;
        float* bulletSpawnsPtr;
        unsigned int* attributesPtr;
        float* bulletVerticesPtr;
        unsigned int* bulletIndicesPtr;

        int verticesLen = 0;
        int indicesLen = 0;
        int bulletSpawnsLen = 0;
        int attributesLen = 0;
        int bulletVerticesLen = 0;
        int bulletIndicesLen = 0;

        AttributesParser();
        AttributesParser(const char*);

        void readFile(const char*);


};

#pragma once

#include <iostream>
#include <fstream>
#include <string>

/* Error Codes
    0: fine
    1: failed file read
    2: Failed to read vertices/indices
    3: invalid setup of the attribute file
*/

/*
 * Attribute Codes:
 *  0: parse stroke stroke stroke width
 *  1: parse bullet spawns
 */

class AttributesParser {


    std::fstream fInStrm;
    int fileLength = 0;
    char extractedChar = 0;
    int currIndex = 0;

    int verticesStart = 0;
    int indicesStart = 0;
    int strokeStart = 0;
    int bulletSpawnsStart = 0;
    int attributesStart = 0;

    std::string vertice;
    std::string indice;
    std::string stroke;
    std::string bulletSpawn;
    std::string attribute;


    void parseAttributes();
    void parseVertices();
    void parseIndices();
    void parseStroke();
    void parseBulletSpawns();

    public:
        int error = 0;

        int numBulletSpawns = 0;

        float* verticesPtr;
        unsigned int* indicesPtr;
        float strokeWidth = 5.0f;
        float* bulletSpawnsPtr;
        unsigned int* attributesPtr;

        int verticesLen = 0;
        int indicesLen = 0;
        int bulletSpawnsLen = 0;
        int attributesLen = 0;

        AttributesParser();
        AttributesParser(const char*);

        void readFile(const char*);


};

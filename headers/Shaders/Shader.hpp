#pragma once

#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Globals.hpp"

using namespace Globals;

/* Error Codes
    1: failed file read
    2: Shader compilation failed
    3: Shader program creation failed
*/

class Shader {
    unsigned int vbo;
    unsigned int vao;
    unsigned int ebo;

    unsigned int vertexShader;
    unsigned int fragmentShader;

    unsigned int shaderProgram;

    std::fstream fInStrm;
    int fileLength;

    float* vertices;
    unsigned int* indices;

    int verticesLength;
    int indicesLength;

    int  success;
    char infoLog[512];

    int error;

    public: 

    Shader();

    Shader(const char*, const char*, float*, int, unsigned int*, int);

    void fileSetup(const char*, const char*);

    void setup(const char*, const char*, float*, int, unsigned int*, int);
    void setupDynamic(const char*, const char*, float*, int, unsigned int*, int);

    void setVertices(float*, int, unsigned int*, int);
    void updateVertices(float*, int, unsigned int*, int); // verts, vlen, ind, indlen

    int getErrorCode();

    void activate();
    
    void draw();

    void set1f(const char*, float);
    void set2f(const char*, float, float);
    void set3f(const char*, float, float, float);
    void set4f(const char*, float, float, float, float);

    void set1i(const char*, int);
    void set2i(const char*, int, int);
    void set3i(const char*, int, int, int);
    void set4i(const char*, int, int, int, int);
};

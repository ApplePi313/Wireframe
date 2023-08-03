#include "Entity/Character.hpp"

Character::Character() {}

Character::Character(const char* characterFile, const char* vertexShaderFile, const char* fragmentShaderFile, float characterWidth, float x, float y) {
    setup(characterFile, vertexShaderFile, fragmentShaderFile, characterWidth, x, y);
}

void Character::setup(const char* characterFile, const char* vertexShaderFile, const char* fragmentShaderFile, float characterWidth, float x, float y) {
    error = 0;

    xPos = x;
    yPos = y;

    width = characterWidth;

    attributesParser.readFile(characterFile);

    hitbox.setCoords(xPos, yPos);
    hitbox.setDimensions(width, width);
    hitbox.setInteractiveProperties(0, 0);

    shader.setup(vertexShaderFile, fragmentShaderFile, attributesParser.verticesPtr, attributesParser.verticesLen, attributesParser.indicesPtr, attributesParser.indicesLen);
}

void Character::getVertices(float** verticesOut, int* verticesLenOut) {
    *verticesOut = new float[attributesParser.verticesLen];
    *verticesOut = attributesParser.verticesPtr;

    *verticesLenOut = attributesParser.verticesLen;
}

void Character::getIndices(unsigned int** indicesOut, int* indicesLenOut) {
    *indicesOut = new unsigned int[attributesParser.indicesLen];
    *indicesOut = attributesParser.indicesPtr;

    *indicesLenOut = attributesParser.indicesLen;
}

int Character::getErrorCode() {
    return error;
}

void Character::activateShader() {
    shader.activate();
}
    
void Character::draw(float windowWidth, float windowHeight, float x, float y) {
    activateShader();

    glLineWidth(attributesParser.strokeWidth);

    shader.set2f("resize", width/2.0f, -width/2.0f);
    shader.set2f("dimensions", width, width);
    shader.set2f("screenDimensions", windowWidth, windowHeight);
    shader.set2f("worldCoords", x, y);
    shader.set2f("coords", xPos, yPos);

    shader.draw();
}

void Character::shoot(int position) {
    if (position < 0 || position >= attributesParser.numBulletSpawns) {
        return;
    }
}

void Character::setCoords(float x, float y) {
    xPos = x;
    yPos = y;

    hitbox.setCoords(xPos, yPos);
}

void Character::translate(float x, float y) {
    xPos += x;
    yPos += y;

    hitbox.setCoords(xPos, yPos);
}

Hitbox Character::getHitbox() {
    return hitbox;
}

void Character::set1f(const char* var, float arg1) {
    activateShader();

    shader.set1f(var, arg1);
}
void Character::set2f(const char* var, float arg1, float arg2) {
    activateShader();
    
    shader.set2f(var, arg1, arg2);
}
void Character::set3f(const char* var, float arg1, float arg2, float arg3) {
    activateShader();
    
    shader.set3f(var, arg1, arg2, arg3);
}
void Character::set4f(const char* var, float arg1, float arg2, float arg3, float arg4) {
    activateShader();
    
    shader.set4f(var, arg1, arg2, arg3, arg4);
}

void Character::set1i(const char* var, int arg1) {
    activateShader();
    
    shader.set1i(var, arg1);
}
void Character::set2i(const char* var, int arg1, int arg2) {
    activateShader();
    
    shader.set2i(var, arg1, arg2);
}
void Character::set3i(const char* var, int arg1, int arg2, int arg3) {
    activateShader();
    
    shader.set3i(var, arg1, arg2, arg3);
}
void Character::set4i(const char* var, int arg1, int arg2, int arg3, int arg4) {
    activateShader();
    
    shader.set4i(var, arg1, arg2, arg3, arg4);
}

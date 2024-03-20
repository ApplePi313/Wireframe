#include "Entity/Character.hpp"

Character::Character() {}

Character::Character(const char* characterFile, const char* vertexShaderFile, const char* fragmentShaderFile, float characterWidth, Coord c) {
    setup(characterFile, vertexShaderFile, fragmentShaderFile, characterWidth, c);
}

void Character::setup(const char* characterFile, const char* vertexShaderFile, const char* fragmentShaderFile, float characterWidth, Coord c) {
    error = 0;

    coords = c;

    width = characterWidth;

    attributesParser.readFile(characterFile);

    hitbox.setCoords(coords);
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
    
void Character::draw(Coord c) {
    activateShader();

    glLineWidth(attributesParser.strokeWidth);

    shader.set2f("resize", width/2.0f, -width/2.0f);
    shader.set2f("dimensions", width, width);
    shader.set2f("worldCoords", c.x, c.y);
    shader.set2f("coords", coords.x, coords.y);

    shader.draw();
}

Bullet Character::shoot(int position) {
    if (position < 0 || position >= attributesParser.numBulletSpawns) {
        return Bullet(Coord(-10, -10), 0, 0, 0, attributesParser.strokeWidth, attributesParser.bulletVerticesPtr, attributesParser.bulletVerticesLen,
                      attributesParser.bulletIndicesPtr, attributesParser.bulletIndicesLen); // lifespan of 0 so that the bullet dies at the next update
    }

    switch (position) {
        case 0:
            return Bullet(coords, 640.0f, 0.0f, 5000, attributesParser.strokeWidth, attributesParser.bulletVerticesPtr, attributesParser.bulletVerticesLen,
                          attributesParser.bulletIndicesPtr, attributesParser.bulletIndicesLen);
    }
}

void Character::setCoords(Coord c) {
    coords = c;

    hitbox.setCoords(coords);
}

void Character::translate(Coord c) {
    coords += c;

    hitbox.setCoords(coords);
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

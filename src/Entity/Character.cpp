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

Bullet Character::shoot(int position, Coord cursorPos) {
    if (position < 0 || position >= attributesParser.numBulletSpawns) {
        return Bullet(Coord(-10, -10), 0, Coord(), 0, 0, "src/Assets/Bullets/default.attr"); // lifespan of 0 so that the bullet dies at the next update
    }

    if (cursorPos.x < coords.x) {
        bulletRotation = ((atan((coords.y - cursorPos.y) / (cursorPos.x - coords.x)) * 180/PI) + 90);
        bulletRotation = 360 - bulletRotation;
    } else if (cursorPos.x == coords.x) {
        bulletRotation = cursorPos.y > coords.y ? 180 : 0;
    } else {
        bulletRotation = ((atan((coords.y - cursorPos.y) / (cursorPos.x - coords.x)) * 180/PI));
        bulletRotation = 90 - bulletRotation;
    }

    switch (position) {
        case 0:
            return Bullet(coords, 640.0f, velocity, bulletRotation, 5000, "src/Assets/Bullets/default.attr");
    }
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

#include "Entity/Hitbox.hpp"

Hitbox::Hitbox() {}

Hitbox::Hitbox(float x, float y, float hitboxWidth, float hitboxHeight) {
    xPos = x;
    yPos = y;
    
    width = hitboxWidth;
    height = hitboxHeight;
}

Hitbox::Hitbox(float x, float y, float hitboxWidth, float hitboxHeight, int hitboxType) {
    xPos = x;
    yPos = y;

    width = hitboxWidth;
    height = hitboxHeight;
    
    type = hitboxType;
}

Hitbox::Hitbox(float x, float y, float hitboxWidth, float hitboxHeight, int hitboxType, int hitboxModifier) {
    xPos = x;
    yPos = y;

    width = hitboxWidth;
    height = hitboxHeight;
    
    type = hitboxType;
    modifier = hitboxModifier;
}

void Hitbox::resize(float hitboxWidth, float hitboxHeight) {
    width = hitboxWidth;
    height = hitboxHeight;
}

void Hitbox::setType(int hitboxType) {
    type = hitboxType;
}
void Hitbox::setModifier(int hitboxModifier) {
    modifier = hitboxModifier;
}
void Hitbox::setInteractiveProperties(int hitboxType, int hitboxModifier) {
    type = hitboxType;
    modifier = hitboxModifier;
}

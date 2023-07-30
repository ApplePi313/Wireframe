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

float Hitbox::getX() {return xPos;}
void Hitbox::setX(float x) {xPos = x;}

float Hitbox::getY() {return yPos;}
void Hitbox::setY(float y) {yPos = y;}

void Hitbox::setCoords(float x, float y) {xPos = x; yPos = y;}

float Hitbox::getWidth() {return width;}
void Hitbox::setWidth(float w) {width = w;}

float Hitbox::getHeight() {return height;}
void Hitbox::setHeight(float h) {height = h;}

void Hitbox::setDimensions(float hitboxWidth, float hitboxHeight) {width = hitboxWidth; height = hitboxHeight;}

int Hitbox::getType() {return type;}
void Hitbox::setType(int hitboxType) {type = hitboxType;}

int Hitbox::getModifier() {return modifier;}
void Hitbox::setModifier(int hitboxModifier) {modifier = hitboxModifier;}

void Hitbox::setInteractiveProperties(int hitboxType, int hitboxModifier) {type = hitboxType; modifier = hitboxModifier;}

bool Hitbox::isColliding(Hitbox otherHitbox) {
    if (xPos < otherHitbox.getX()) {
        if (yPos < otherHitbox.getY()) {
            return (otherHitbox.getX() - xPos < width && otherHitbox.getY() - yPos < height); // other hitbox is to bottom right

        } else {
            return (otherHitbox.getX() - xPos < width && yPos - otherHitbox.getY() < otherHitbox.getHeight()); // other hitbox is to top right

        }
    } else {
        if (yPos < otherHitbox.getY()) {
            return (xPos - otherHitbox.getX() < otherHitbox.getWidth() && otherHitbox.getY() - yPos < height); // other hitbox is to bottom left

        } else {
            return (xPos - otherHitbox.getX() < otherHitbox.getWidth() && yPos - otherHitbox.getY() < otherHitbox.getHeight()); // other hitbox is to top left

        }
    }
}

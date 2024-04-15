#include "Entity/Hitbox.hpp"

Hitbox::Hitbox() {}

Hitbox::Hitbox(Coord c, int hitboxWidth, int hitboxHeight) {
    coords = c;
    
    width = hitboxWidth;
    height = hitboxHeight;
}

Hitbox::Hitbox(Coord c, int hitboxWidth, int hitboxHeight, int hitboxType) {
    coords = c;

    width = hitboxWidth;
    height = hitboxHeight;
    
    type = hitboxType;
}

Hitbox::Hitbox(Coord c, int hitboxWidth, int hitboxHeight, int hitboxType, int hitboxModifier) {
    coords = c;

    width = hitboxWidth;
    height = hitboxHeight;
    
    type = hitboxType;
    modifier = hitboxModifier;
}

int Hitbox::getX() {return coords.x;}
void Hitbox::setX(int x) {coords.y = x;}

int Hitbox::getY() {return coords.y;}
void Hitbox::setY(int y) {coords.y = y;}

void Hitbox::setCoords(Coord c) { coords = c; }
Coord Hitbox::getCoords() { return coords; }
void Hitbox::translate(Coord c) { coords += c; }

int Hitbox::getWidth() {return width;}
void Hitbox::setWidth(int w) {width = w;}

int Hitbox::getHeight() {return height;}
void Hitbox::setHeight(int h) {height = h;}

void Hitbox::setDimensions(int hitboxWidth, int hitboxHeight) {width = hitboxWidth; height = hitboxHeight;}

int Hitbox::getType() {return type;}
void Hitbox::setType(int hitboxType) {type = hitboxType;}

int Hitbox::getModifier() {return modifier;}
void Hitbox::setModifier(int hitboxModifier) {modifier = hitboxModifier;}

void Hitbox::setInteractiveProperties(int hitboxType, int hitboxModifier) {type = hitboxType; modifier = hitboxModifier;}

bool Hitbox::isColliding(Hitbox otherHitbox) {
    if (coords.x < otherHitbox.getX()) {
        if (coords.y < otherHitbox.getY()) {
            return (otherHitbox.getX() - coords.x < width && otherHitbox.getY() - coords.y < height); // other hitbox is to bottom right

        } else {
            return (otherHitbox.getX() - coords.x < width && coords.y - otherHitbox.getY() < otherHitbox.getHeight()); // other hitbox is to top right

        }
    } else {
        if (coords.y < otherHitbox.getY()) {
            return (coords.x - otherHitbox.getX() < otherHitbox.getWidth() && otherHitbox.getY() - coords.y < height); // other hitbox is to bottom left

        } else {
            return (coords.x - otherHitbox.getX() < otherHitbox.getWidth() && coords.y - otherHitbox.getY() < otherHitbox.getHeight()); // other hitbox is to top left

        }
    }
}

bool Hitbox::isBlocking() {
    return (type == 1 || type == 3);
}

#include "Entity/Entity.hpp"


int Entity::getErrorCode() {
    return error;
}

void Entity::activateShader() {
    shader.activate();
}
void Entity::draw(Coord c) {
    activateShader();

    glLineWidth(attributesParser.strokeWidth);

    shader.set2f("resize", width/2.0f, -width/2.0f);
    shader.set2f("dimensions", width, width);
    shader.set2f("worldCoords", c.x, c.y);
    shader.set2f("coords", coords.x, coords.y);

    shader.draw();
}

void Entity::setCoords(Coord c) {
    coords = c;

    hitbox.setCoords(coords);
}
void Entity::translate(Coord c) {
    coords += c;

    velocity = c * (currTimeMillis() - lastUpdateTime);
    lastUpdateTime = currTimeMillis();

    hitbox.setCoords(coords);
}

Hitbox Entity::getHitbox() {
    return hitbox;
}
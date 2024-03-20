#include "Entity/Bullet.hpp"

Bullet::Bullet() {}

Bullet::Bullet(Coord pos, float bulletVelocity, float bulletRotation, long bulletLifespan, float bulletStrokeWidth,
               float* bulletVertices, int bulletVerticesLen, unsigned int* bulletIndices, int bulletIndicesLen) {
    setup(pos, bulletVelocity, bulletRotation, bulletLifespan, bulletStrokeWidth, bulletVertices, bulletVerticesLen, bulletIndices, bulletIndicesLen);
}

void Bullet::setup(Coord pos, float bulletVelocity, float bulletRotation, long bulletLifespan, float bulletStrokeWidth,
                   float* bulletVertices, int bulletVerticesLen, unsigned int* bulletIndices, int bulletIndicesLen) {
    coords = pos;

    velocityMagnitude = bulletVelocity;
    rotation = bulletRotation;

    velocity.x = sin(rotation) * velocityMagnitude;
    velocity.y = -cos(rotation) * velocityMagnitude;

    lifespan = bulletLifespan;

    strokeWidth = bulletStrokeWidth;

    vertices = bulletVertices;
    verticesLen = bulletVerticesLen;
    indices = bulletIndices;
    indicesLen = bulletIndicesLen;

    spawnTime = currTimeMillis();
    lastUpdateTime = spawnTime;
}

Signal Bullet::signal(Signal signal) {
    switch (signal.type) {
        case SignalType::Ignore:
            returnSignal.type = SignalType::Ignore;
            break;

        case SignalType::Update:
            if ((currTimeMillis() - spawnTime) > lifespan) {
                returnSignal = {SignalType::Delete, 0};
                break;
            }

            coords += velocity * ((currTimeMillis() - lastUpdateTime) / 1000.0);

            lastUpdateTime = currTimeMillis();
            returnSignal.type = SignalType::Ignore;
            break;

        default:
            returnSignal = {SignalType::Invalid, 0};
            break;
    }
    return returnSignal;
}

void Bullet::draw(Shader* shader) {
    glLineWidth(strokeWidth);

    (*shader).updateVertices(vertices, verticesLen, indices, indicesLen);
    (*shader).set2f("coords", coords.x, coords.y);
    (*shader).draw();
}
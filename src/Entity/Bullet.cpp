#include "Entity/Bullet.hpp"

Bullet::Bullet() {}

Bullet::Bullet(Coord pos, float bulletVelocity, Coord initialV, float bulletRotation, long bulletLifespan, const char* bulletsAttrFile) {
    setup(pos, bulletVelocity, initialV, bulletRotation, bulletLifespan, bulletsAttrFile);
}

void Bullet::setup(Coord pos, float bulletVelocity, Coord initialV, float bulletRotation, long bulletLifespan, const char* bulletsAttrFile) {
    coords = pos;
    attributesParser.readFile(bulletsAttrFile);

    velocityMagnitude = bulletVelocity;
    rotation = bulletRotation;

    velocity.x = sin(rotation * PI/180) * velocityMagnitude;
    velocity.y = -cos(rotation * PI/180) * velocityMagnitude;

    velocity += initialV;
    // initialV.print();

    lifespan = bulletLifespan;

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
    glLineWidth(attributesParser.strokeWidth);

    (*shader).updateVertices(attributesParser.verticesPtr, attributesParser.verticesLen, 
                             attributesParser.indicesPtr, attributesParser.indicesLen);
    (*shader).set2f("coords", coords.x, coords.y);
    (*shader).draw();
}
#include "Entity/Bullet.hpp"

Bullet::Bullet(){}

Bullet::Bullet(float bulletX, float bulletY, float bulletVelocity, float bulletRotation, int bulletLifespan) {
    setup(bulletX, bulletY, bulletVelocity, bulletRotation, bulletLifespan);
}

void Bullet::setup(float bulletX, float bulletY, float bulletVelocity, float bulletRotation, int bulletLifespan) {
    xPos = bulletX;
    yPos = bulletY;

    velocity = bulletVelocity;
    rotation = bulletRotation;

    spawnTime = (long) std::time(nullptr);
}

void Bullet::update() {
    
}

bool Bullet::isDead() {
    return dead;
}

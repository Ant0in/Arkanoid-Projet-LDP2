#include "laser.hpp"

SolidRectangle& Laser::getHitbox() {
    return _hitbox;
}
const SolidRectangle& Laser::getHitbox() const {
    return _hitbox;
}

Position2D Laser::getPosition() const {
    return getHitbox().getPosition();
}
void Laser::setPosition(const Position2D& p) {
    getHitbox().setPosition(p);
}

float Laser::getSpeed() {
    return _speed;
}

Position2D Laser::calculateNewPosition() {
    return Position2D(getPosition().getX(), getPosition().getY() - getSpeed());
}

void Laser::spawnLaser(Racket* r) {
    Position2D r_center = r->getCenterPosition();
    Position2D offset_center =
        Position2D(r_center.getX() - LASER_WIDTH / 2, r->getPosition().getY());
    setPosition(offset_center);
}

bool Laser::operator==(Laser* other) {
    return ((getPosition() == other->getPosition()) && (getSpeed() == other->getSpeed()));
}
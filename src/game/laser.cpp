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
    // the laser is spawned at the center of the racket.
    // we create a default laser at first, and then call spawn with the racket passed as an argument
    Position2D r_center = r->getCenterPosition();
    Position2D offset_center =
        Position2D(r_center.getX() - LASER_WIDTH / 2, r->getPosition().getY());
    setPosition(offset_center);
}

bool Laser::operator==(Laser* other) {
    // written to help with removing laser from a vector
    return ((getPosition() == other->getPosition()) && (getSpeed() == other->getSpeed()));
}
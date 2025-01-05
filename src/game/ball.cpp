#include "../../include/ball.hpp"

SolidCircle& Ball::getHitbox() {
    return _hitbox;
}
const SolidCircle& Ball::getHitbox() const {
    return _hitbox;
}

Position2D Ball::getCenterPosition() const {
    return getHitbox().getPosition();
}
void Ball::setCenterPosition(const Position2D& pos) {
    getHitbox().setPosition(pos);
}

float Ball::getRadius() const {
    return getHitbox().getRadius();
}
void Ball::setRadius(float r) {
    getHitbox().setRadius(r);
}

std::tuple<float, float> Ball::getVelocity() const {
    return std::make_tuple(_x_velocity, _y_velocity);
}
void Ball::setVelocity(float xv, float yv) {
    _x_velocity = xv;
    _y_velocity = yv;
}

float Ball::getSpeed() const {
    return _speed;
}
void Ball::setSpeed(float s) {
    _speed = s;
}

bool Ball::isAlive() const {
    return _is_alive;
}
void Ball::setAlive(bool flag) {
    _is_alive = flag;
}

Position2D Ball::calculateNewPosition() {
    auto [x_vel, y_vel] = getVelocity();
    float speed         = getSpeed();

    float dx = getCenterPosition().getX() + (x_vel * speed);
    float dy = getCenterPosition().getY() + (y_vel * speed);

    return Position2D(dx, dy);
}

bool Ball::operator==(Ball* other) const {
    // written to help with removing ball from a vector
    return (getCenterPosition() == other->getCenterPosition()) &&
           (getRadius() == other->getRadius()) && (getHitbox() == other->getHitbox()) &&
           (getVelocity() == other->getVelocity()) && (getSpeed() == other->getSpeed());
}
#include "ball.hpp"


Position2D Ball::getCenterPosition() const {return center;}
void Ball::setCenterPosition(Position2D pos) {center = pos;}

float Ball::getRadius() const {return radius;}
void Ball::setRadius(float r) {radius = r;}

SolidCircle& Ball::getHitbox() {return hitbox;}
const SolidCircle& Ball::getHitbox() const {return hitbox;}

std::tuple<float, float> Ball::getVelocity() const {return std::make_tuple(x_velocity, y_velocity);}
void Ball::setVelocity(float xv, float yv) {x_velocity = xv; y_velocity = yv;}

float Ball::getSpeed() const {return speed;}
void Ball::setSpeed(float s) {speed = s;}

void Ball::moveToCoordinates(const Position2D& coord) {
    // Move the ball with its hitbox
    setCenterPosition(coord);
    getHitbox().setPosition(coord);
}

#include "ball.hpp"

SolidCircle& Ball::getHitbox() {return hitbox;}
const SolidCircle& Ball::getHitbox() const {return hitbox;}

Position2D Ball::getCenterPosition() const {return getHitbox().getPosition();}
void Ball::setCenterPosition(const Position2D& pos) {getHitbox().setPosition(pos);}

float Ball::getRadius() const {return getHitbox().getRadius();}
void Ball::setRadius(float r) {getHitbox().setRadius(r);}

std::tuple<float, float> Ball::getVelocity() const {return std::make_tuple(x_velocity, y_velocity);}
void Ball::setVelocity(float xv, float yv) {x_velocity = xv; y_velocity = yv;}

float Ball::getSpeed() const {return speed;}
void Ball::setSpeed(float s) {speed = s;}

bool Ball::isAlive() const {return is_alive;}
void Ball::setAlive(bool flag) {is_alive = flag;}

Position2D Ball::calculateNewPosition(){
    auto [x_vel, y_vel] = getVelocity();
    float speed = getSpeed();

    float dx = getCenterPosition().getX() + (x_vel * speed);
    float dy = getCenterPosition().getY() + (y_vel * speed);

    return Position2D(dx, dy);
}

bool Ball::operator==(const Ball& other) const{
    return (getCenterPosition() == other.getCenterPosition()) && (getRadius() == other.getRadius());
}
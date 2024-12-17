#include "racket.hpp"

Position2D Racket::getPosition() const {return position;}
void Racket::setPosition(const Position2D& pos) {position = pos;}

float Racket::getHeight() const {return height;}
float Racket::getWidth() const {return width;}

void Racket::setHeight(float h) {height = h;}
void Racket::setWidth(float w) {width = w;}

SolidRectangle& Racket::getHitbox() {return hitbox;}
const SolidRectangle& Racket::getHitbox() const {return hitbox;}


float Racket::getSensibility() const {return sensibility;}
void Racket::setSensitivity(float s) {sensibility = s;}

Position2D Racket::calculateCenterPosition() const {
    float cx = getPosition().getX() + getWidth() / 2;
    float cy = getPosition().getY() + getHeight() / 2;
    return Position2D(cx, cy);
}

void Racket::moveToCoordinates(const Position2D& coord){
    // Move racket with its hitbox
    setPosition(coord);
    getHitbox().setPosition(coord);
}

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

Position2D Racket::getCenterPosition() const{return getHitbox().getCenterPosition();}

Position2D Racket::calculateNewPosition(const Action& action){
    float x = getPosition().getX();
    float y = getPosition().getY();
    float sens = getSensibility();

    switch (action) {
        case Action::LEFT:
            return Position2D(x - sens, y);
        case Action::RIGHT:
            return Position2D(x + sens, y);
        case Action::NONE:
            return Position2D(x, y);
        default:
            throw std::runtime_error("Action not implemented");
    }
}

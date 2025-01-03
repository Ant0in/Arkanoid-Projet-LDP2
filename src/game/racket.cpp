#include "racket.hpp"

SolidRectangle& Racket::getHitbox() {return _hitbox;}
const SolidRectangle& Racket::getHitbox() const {return _hitbox;}

Position2D Racket::getPosition() const {return getHitbox().getPosition();}
void Racket::setPosition(const Position2D& pos) {getHitbox().setPosition(pos);}

float Racket::getHeight() const {return getHitbox().getHeight();}
float Racket::getWidth() const {return getHitbox().getWidth();}

void Racket::setHeight(float h) {getHitbox().setHeight(h);}
void Racket::setWidth(float w) {getHitbox().setWidth(w);}

float Racket::getSensibility() const {return _sensibility;}
void Racket::setSensitivity(float s) {_sensibility = s;}

Position2D Racket::getCenterPosition() const{return getHitbox().getCenterPosition();}

Position2D Racket::calculateNewPosition(const Action& action){
    float x = getPosition().getX();
    float y = getPosition().getY();
    float sens = getSensibility();

    switch (action) {
        case Action::LEFT:
            // std::cout<<"left"<<std::endl;
            return Position2D(x - sens, y);
        case Action::RIGHT:
            // std::cout<<"right"<<std::endl;
            return Position2D(x + sens, y);
        case Action::NONE:
            return Position2D(x, y);
        default:
            throw std::runtime_error("Action not implemented");
    }
}
